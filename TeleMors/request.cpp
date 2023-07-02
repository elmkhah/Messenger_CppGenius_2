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
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    QString messageRes=jsonObj.value("message").toString();
    int result=resultCode.toInt();
    if(result==200){
        if(messageRes=="You are already logged in!"){
            Request::logout(_user);
        }
        makedir.makeDirectory();
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

int Request::createChat(QString _token,QString type,QString _name)
{
    QString url;
    int numOfChats;
    MyFile writeRead;
    //***url***
    url+=baseUrl+"create"+type+"?token="+_token+"&"+type+"_name="+_name;

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    QString messageResult=jsonObj.value("message").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add channel to files***

        writeRead.writeNumberOfMessage(0,type,_name);

        Request::joinChat(_token,type,_name);
    }
    else if(result==401&&messageResult=="token is not Correct"){
        url.erase(url.begin(),url.end());
        User myUser(writeRead.readUsernamePassword()[0],true,writeRead.readUsernamePassword()[1],_token);
        Request::logout(myUser);
        Request::login(myUser);
        url+=baseUrl+"create"+type+"?token="+myUser.getToken()+"&"+type+"_name="+_name;
        jsonObj = Request::sendRequest(url);
         qDebug()<<url;
        if(!jsonObj.isEmpty()){
           resultCode=jsonObj.value("code").toString();
            result=resultCode.toInt();
            if(result==200){
                writeRead.writeNumberOfMessage(0,type,_name);

                Request::joinChat(myUser.getToken(),type,_name);
            }
            return result;
        }
        return OFFLINE;
    }
    return result;
    }
    return OFFLINE;
}

int Request::joinChat(QString _token,QString type,QString _name)
{

    QString url;
    int numOfChats;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"join"+type+"?token="+_token+"&"+type+"_name="+_name;

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){

    QString resultCode=jsonObj.value("code").toString();
    QString resultMessage=jsonObj.value("message").toString();
    int result=resultCode.toInt();
    if(result==200&resultMessage!="You are already Joined!"){
        //***add chat to files***

        writeRead.addNameTitel(type,_name);

        //add number of chat
        numOfChats=writeRead.readNumberOfChats(type);
        writeRead.writeNumberOfChats(numOfChats+1,type);
        //set admin for channel if type of chat is channel
        if(type=="channel"){
        QVector<QString>myUserInfo=writeRead.readUsernamePassword();
        bool candeterminate=writeRead.setChannelAdmin(myUserInfo[0],_name);
        if(!candeterminate){
            Date currentTime;
            User myUser(myUserInfo[0],true,myUserInfo[1],_token);
            Message DetermineStatusAdmin(myUser,currentTime.getCurrentTime(),"createchannel");
            int res=Request::sendMessageChat("channel",_name,DetermineStatusAdmin);
            if(res==200) writeRead.setChannelAdmin(_name,1);//set admin
            else writeRead.setChannelAdmin(_name,0);//set isn't admin
        }
        }
         Request::getChatMessages(_token,type,_name);

    }
    else if(result==401&&resultMessage=="token is not Correct"){
         url.erase(url.begin(),url.end());
         User myUser(writeRead.readUsernamePassword()[0],true,writeRead.readUsernamePassword()[1],_token);
         Request::logout(myUser);
         Request::login(myUser);
         url+=baseUrl+"join"+type+"?token="+myUser.getToken()+"&"+type+"_name="+_name;
         jsonObj = Request::sendRequest(url);
         if(!jsonObj.isEmpty()){
         resultCode=jsonObj.value("code").toString();
        resultMessage=jsonObj.value("message").toString();
         result=resultCode.toInt();
        if(result==200&resultMessage!="You are already Joined!"){
            //***add chat to files***

            writeRead.addNameTitel(type,_name);

            //add number of chat
            numOfChats=writeRead.readNumberOfChats(type);
            writeRead.writeNumberOfChats(numOfChats+1,type);
            //set admin for channel if type of chat is channel
            if(type=="channel"){
                QVector<QString>myUserInfo=writeRead.readUsernamePassword();
                bool candeterminate=writeRead.setChannelAdmin(myUserInfo[0],_name);
                if(!candeterminate){
                    Date currentTime;
                    User myUser1(myUserInfo[0],true,myUserInfo[1],myUser.getToken());
                    Message DetermineStatusAdmin(myUser1,currentTime.getCurrentTime(),"createchannel");
                    int res=Request::sendMessageChat("channel",_name,DetermineStatusAdmin);
                    if(res==200) writeRead.setChannelAdmin(_name,1);//set admin
                    else writeRead.setChannelAdmin(_name,0);//set isn't admin
                }
            }
            Request::getChatMessages(myUser.getToken(),type,_name);
         }
        return result;
    }
         return OFFLINE;
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
    QString messageRes=jsonObj.value("message").toString();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of chats***********
        int numberOfUsers=Request::calculate(messageResult);
        if(type=="user") type="private";
        // add chat to file
        writeRead.writeNumberOfChats(numberOfUsers,type);

        writeRead.writeMessages(numberOfUsers,type,jsonObj);
    }
    else if(result==401&&messageRes=="token is not Correct"){
        url.erase(url.begin(),url.end());
        User myUser(writeRead.readUsernamePassword()[0],true,writeRead.readUsernamePassword()[1],_token);
        Request::logout(myUser);
        Request::login(myUser);
        url+=baseUrl+"get"+type+"list?token="+myUser.getToken();
        qDebug()<<url;
        jsonObj = Request::sendRequest(url);
        resultCode=jsonObj.value("code").toString();
        result=resultCode.toInt();
        messageRes=jsonObj.value("message").toString();
         if(!jsonObj.isEmpty()){
        if(result==200)    {
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
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageChat(QString type,QString _chatName,const Message& _msg)
{
    if(type=="private")type="user";
    MyFile writeRead;
    QString url;
    //***url***
    url+=baseUrl+"sendmessage"+type+"?token="+_msg.getSender().getToken()+"&dst="+_chatName+"&body="+_msg.getMessageBody();
    qDebug()<<url;


    QJsonObject jsonObj = Request::sendRequest(url);

    if(!jsonObj.isEmpty()){

    QString resultCode=jsonObj.value("code").toString();
    QString resultMessage=jsonObj.value("message").toString();
    int result=resultCode.toInt();
    if(result==401&&resultMessage=="token is not Correct"){
         url.erase(url.begin(),url.end());
         User myUser(writeRead.readUsernamePassword()[0],true,writeRead.readUsernamePassword()[1]);
         Request::logout(myUser);
         Request::login(myUser);
         url+=baseUrl+"sendmessage"+type+"?token="+myUser.getToken()+"&dst="+_chatName+"&body="+_msg.getMessageBody();
          jsonObj = Request::sendRequest(url);
         if(!jsonObj.isEmpty()){
        resultCode=jsonObj.value("code").toString();
        result=resultCode.toInt();
        return result;
          }
         return OFFLINE;
    }
    return result;
    }
    return OFFLINE;
}

int Request::getChatMessages(QString _token, QString type, QString _dst)
{

    if(type=="private")type="user";
    QString url;
     MyFile writeRead;
    //***url***
    url+=baseUrl+"get"+type+"chats?token="+_token+"&dst="+_dst;
    if(type=="user")type="private";
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of message with dst chat***********
        int numberOfChats=Request::calculate(messageResult);
        writeRead.writeNumberOfMessage(numberOfChats,type,_dst);
        writeRead.writeMessages(numberOfChats,type,_dst,jsonObj,true);
        if(!writeRead.existChats("channel",_dst+".isAdmintxt")){
        if(type=="channel"){

            QVector<QString>myUserInfo=writeRead.readUsernamePassword();

            bool candeterminate=writeRead.setChannelAdmin(myUserInfo[0],_dst);
            if(!candeterminate){
                Date currentTime;
                User myUser(myUserInfo[0],true,myUserInfo[1],_token);
                Message DetermineStatusAdmin(myUser,currentTime.getCurrentTime(),"createchannel");
                int res=Request::sendMessageChat("channel",_dst,DetermineStatusAdmin);
                if(res==200){
                    writeRead.setChannelAdmin(_dst,1);//set admin
                }
                else {
                    writeRead.setChannelAdmin(_dst,0);//set isn't admin
            }
            }
        }

        }



    }
    return result;
    }
    return OFFLINE;
    }

int Request::getChatMessages(QString _token,QString type,QString _dst, QString _date)
{

    if(type=="private")type="user";
    QString url;
    //***url***
    url+=baseUrl+"get"+type+"chats?token="+_token+"&dst="+_dst;
    if(type=="user")type="private";
    //********add data if parametr data send***//////
    url+="&date="+_date;
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
                    write.writeMessages(numberOfChats,type,_dst,jsonObj,false);

    }

                return result;
    }
    return OFFLINE;
    }

