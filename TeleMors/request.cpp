#include "request.h"
#include<QCoreApplication>
#define OFFLINE 500

Request::Request()
{
    baseUrl="http://api.barafardayebehtar.ml:8080/";
}

QJsonObject Request::sendRequest(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    if (reply->error() == QNetworkReply::NoError) {
    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    reply->deleteLater();
    return jsonObj;
    }
     else {
    if (reply->error() == QNetworkReply::HostNotFoundError) {

    }
    reply->deleteLater();
    return QJsonObject();

    }
}

int Request::calculate(QString messageResult)
{
    int i=0;
    QString num="";
    while(messageResult[i]!='-')
    i++;
    i++;
    while(messageResult[i]!='-'){
    num+=messageResult[i];
    i++;
    }
    int numberOfChats=num.toInt();
    return numberOfChats;
}

int Request::login(User &_user)
{
    QString url;
    url+=baseUrl+"login?username="+_user.getUsername()+"&password="+_user.getPassword();

    MyFile makedir;
    makedir.makeDirectory();

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
         QString _token=jsonObj.value("token").toString();
        _user.setToken(_token);
         MyFile write;
        write.loginFile(_user);
       }
    return result;
    }

    return OFFLINE;
}

int Request::signup(User& _user){
    QString url;
    url+=baseUrl+"signup?username="+_user.getUsername()+"&password="+_user.getPassword();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    return result;
    }
    return OFFLINE;

}

int Request::logout(User & _user)
{
    QString url;
    url+=baseUrl+"logout?username="+_user.getUsername()+"&password="+_user.getPassword();

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        MyFile write;
        write.logoutFile();
    }
    return result;
    }
    return OFFLINE;
}

int Request::createChat(QString _token,QString type,QString _name, QString _title)
{
    QString url;
    int numOfChats;
    MyFile writeRead;
    //***url***
    url+=baseUrl+"create"+type+"?token="+_token+"&"+type+"_name="+_name+"&"+type+"_title="+_title;


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add channel to files***
        writeRead.addNameTitel(type,_name,_title);

        writeRead.writeNumberOfMessage(0,type,_name);

        //add number of chats
        numOfChats=writeRead.readNumberOfChats(type);

        writeRead.writeNumberOfChats(numOfChats+1,type);
        Request::joinChat(_token,type,_name);
    }
    return result;
    }
    return OFFLINE;
}

int Request::joinChat(QString _token,QString type,QString _name)
{
    QString _title="0";
    QString url;
    int numOfChats;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"join"+type+"?token="+_token+"&"+type+"_name="+_name;

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){

    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        //***add chat to files***

        writeRead.addNameTitel(type,_name,_title);

        //add number of chat
        numOfChats=writeRead.readNumberOfChats(type);
        writeRead.writeNumberOfChats(numOfChats+1,type);
        //set admin for channel if type of chat is channel
        if(type=="channel"){
        QVector<QString>myUserInfo=writeRead.readUsernamePassword();
        bool candeterminate=writeRead.setChannelAdmin(myUserInfo[0],_name);
        if(!candeterminate){
            Date currentTime;
            User myUser(myUserInfo[0],true,_token,myUserInfo[1]);
            Message DetermineStatusAdmin(myUser,currentTime.getCurrentTime(),"create channel");
            int res=Request::sendMessageChat("channel",_name,DetermineStatusAdmin);
            if(res==200) writeRead.setChannelAdmin(_name,1);//set admin
            else writeRead.setChannelAdmin(_name,0);//set isn't admin
        }
        }
         Request::getChatMessages(_token,type,_name);

    }

    return result;
    }
    return OFFLINE;
}

int Request::getChatList(QString _token,QString type)
{
    if(type=="private") type="user";
    QString url;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"get"+type+"list?token="+_token;

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of chats***********
        int numberOfUsers=Request::calculate(messageResult);
        if(type=="user") type="private";
        // add chat to file
        writeRead.writeNumberOfChats(numberOfUsers,type);
        writeRead.writeMessages(numberOfUsers,type,jsonObj);
    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageChat(QString type,QString _chatName, Message _msg)
{
    if(type=="private")type="user";
    MyFile writeRead;
    QString url;
    //***url***
    url+=baseUrl+"sendmessage"+type+"?token="+_msg.getSender().getToken()+"&dst="+_chatName+"&body="+_msg.getMessageBody();
    if(type=="user")type="private";
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        if(type=="private"){
                MyFile writeRead;
                //*********check user chat history************
                int numOfChats;
                if(writeRead.existChats(type,_chatName)){
                    Request::getChatMessages(_msg.getSender().getToken(),type,_chatName,writeRead.getTimeLastMessage(type,_chatName));

                }

                else{
                  Request::getChatMessages(_msg.getSender().getToken(),type,_chatName,writeRead.getTimeLastMessage(type,_chatName));


                    //add number of private chats

                    numOfChats=writeRead.readNumberOfChats(type);
                    writeRead.writeNumberOfChats(numOfChats+1,type);
                }

        }
        else{
        QString lastMessageTime=writeRead.getTimeLastMessage(type,_chatName);
        if(lastMessageTime=="Empty"){
            Request::getChatMessages(_msg.getSender().getToken(),type,_chatName);
        }
        else{
            Date lastMessage;
            lastMessage.setRowDate(lastMessageTime);
            Request::getChatMessages(_msg.getSender().getToken(),type,_chatName,lastMessage);
        }
    }
    }
    return result;
    }
    return OFFLINE;
}

int Request::getChatMessages(QString _token,QString type,QString _dst, Date _date)
{
    if(type=="private")type="user";
    QString url;
    //***url***
    url+=baseUrl+"get"+type+"chats?token="+_token+"&dst="+_dst;
    if(type=="user")type="private";
    if(_date.getRowDate()==Date().getRowDate()){
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
        QString resultCode=jsonObj.value("code").toString();
        int result=resultCode.toInt();
        if(result==200){
                QString messageResult=jsonObj.value("message").toString();
                //*******calculate number of message with dst chat***********
                int numberOfChats=Request::calculate(messageResult);
                MyFile write;
                write.writeNumberOfMessage(numberOfChats,type,_dst);
                write.writeMessages(numberOfChats,type,_dst,jsonObj);


    }
        return result;
    }
    return OFFLINE;
    }
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
                QString resultCode=jsonObj.value("code").toString();
                int result=resultCode.toInt();
                if(result==200){
                    QString messageResult=jsonObj.value("message").toString();
                    //*******calculate number of message with dst chat***********
                    int numberOfChats=Request::calculate(messageResult);
                    MyFile write;
                    int numOfperviousMessages=write.readNumberOfMessage(type,_dst);
                    write.writeNumberOfMessage(numberOfChats+numOfperviousMessages,type,_dst);
                    write.writeMessages(numberOfChats,type,_dst,jsonObj);

    }

                return result;
    }
    return OFFLINE;
    }

}
