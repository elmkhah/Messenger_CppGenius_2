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

QString Request::getToken()
{
    MyFile read;
    return read.getToken();
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
        write.loginFile(_token);
        write.addUsernamePassword(_user.getUsername(),_user.getPassword());
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

int Request::createGroup(QString _token,QString _name,QString _title){
    QString url;
    int numOfChats;
    MyFile writeRead;
    //***url***
    url+=baseUrl+"creategroup?token="+_token+"&group_name="+_name+"&group_title="+_title;


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add group to files***
        writeRead.addNameTitel("group",_name,_title);

        writeRead.writeNumberOfMessage(0,"group",_name);

        writeRead.createChat("group",_name);

        //add number of groups
        numOfChats=writeRead.readNumberOfChats("group");

        writeRead.writeNumberOfChats(numOfChats+1,"group");
    }
    return result;
    }
    return OFFLINE;
}

int Request::createChannel(QString _token,QString _name, QString _title)
{
    QString url;
    int numOfChats;
    MyFile writeRead;
    //***url***
    url+=baseUrl+"createchannel?token="+_token+"&channel_name="+_name+"&channel_title="+_title;


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add channel to files***
        writeRead.addNameTitel("channel",_name,_title);

        writeRead.writeNumberOfMessage(0,"channel",_name);
        //set isAdmin

           writeRead.writeMessages("channel",_name,1);
        //add number of channels
        numOfChats=writeRead.readNumberOfChats("channel");

        writeRead.writeNumberOfChats(numOfChats+1,"channel");
    }
    return result;
    }
    return OFFLINE;
}

int Request::joinGroup(QString _token,QString _name)
{
    QString _title="0";
    QString url;
    int numOfChats;
    MyFile writeRead;
     //***url***
    url+=baseUrl+"joingroup?token="+_token+"&group_name="+_name;
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        //***add group to files***

        writeRead.addNameTitel("group",_name,_title);
        //add number of groups

        numOfChats=writeRead.readNumberOfChats("group");

        writeRead.writeNumberOfChats(numOfChats+1,"group");

        Request::getGroupChats(_token,_name);

    }
    return result;
    }
    return OFFLINE;
}

int Request::joinChannel(QString _token,QString _name)
{
    QString _title="0";
    QString url;
    int numOfChats;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"joinchannel?token="+_token+"&channel_name="+_name;

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){

    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        //***add channel to files***

        writeRead.addNameTitel("channel",_name,_title);

        //add number of channels
        numOfChats=writeRead.readNumberOfChats("chennel");
        writeRead.writeNumberOfChats(numOfChats+1,"channel");

        //set isAdmin
        writeRead.writeMessages("channel",_name,0);

         Request::getChannelChats(_token,_name);

    }

    return result;
    }
    return OFFLINE;
}

int Request::getGroupList(QString _token)
{
    QString url;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"getgrouplist?token="+_token;


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of groups***********
        int numberOfGroups=Request::calculate(messageResult);
        // add groups to file
        writeRead.writeNumberOfChats(numberOfGroups,"group");
            writeRead.writeMessages(numberOfGroups,"group",jsonObj);
    }
    return result;
    }
    return OFFLINE;
}

int Request::getChannelList(QString _token)
{
    QString url;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"getchannellist?token="+_token;

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of channels***********

        int numberOfChannels=Request::calculate(messageResult);
        // add channels to file
        writeRead.writeNumberOfChats(numberOfChannels,"channel");
       writeRead.writeMessages(numberOfChannels,"channel",jsonObj);
    }
    return result;
    }
    return OFFLINE;
}

int Request::getUserList(QString _token)
{
    QString url;
    MyFile writeRead;
        //***url***
    url+=baseUrl+"getuserlist?token="+_token;


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of users***********
        int numberOfUsers=Request::calculate(messageResult);

        // add users to file
        writeRead.writeNumberOfChats(numberOfUsers,"private");
        writeRead.writeMessages(numberOfUsers,"private",jsonObj);
    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageUser(User &_dst, Message _msg)
{
    QString url;
    int numOfChats;
        //***url***
    url+=baseUrl+"sendmessageuser?token="+_msg.getSender().getToken()+"&dst="+_dst.getUsername()+"&body="+_msg.getMessageBody();

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
         MyFile writeRead;
        //*********check user chat history************

         if(writeRead.existChats("private",_dst.getUsername())){
                writeRead.writeMessages("private",_dst.getUsername(),_msg);

                numOfChats=writeRead.readNumberOfMessage("private",_dst.getUsername());

                writeRead.writeNumberOfMessage(numOfChats+1,"private",_dst.getUsername());
        }

        else{
                writeRead.writeMessages("private",_dst.getUsername(),_msg);

            //add number of private chats

                numOfChats=writeRead.readNumberOfChats("private");
                writeRead.writeNumberOfChats(numOfChats+1,"private");
        }

    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageGroup(QString _groupName, Message _msg)
{
    QString url;
    //***url***
    url+=baseUrl+"sendmessagegroup?token="+_msg.getSender().getToken()+"&dst="+_groupName+"&body="+_msg.getMessageBody();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        int numOfChats;

        MyFile writeRead;
        writeRead.writeMessages("group",_groupName,_msg);

        numOfChats=writeRead.readNumberOfMessage("group",_groupName);

        writeRead.writeNumberOfMessage(numOfChats+1,"group",_groupName);
    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageChannel(QString _channelName, Message _msg)
{
    QString url;
    //***url***
    url+=baseUrl+"sendmessagechannel?token="+_msg.getSender().getToken()+"&dst="+_channelName+"&body="+_msg.getMessageBody();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        int numOfChats;

        MyFile writeRead;
        writeRead.writeMessages("channel",_channelName,_msg);

        numOfChats=writeRead.readNumberOfMessage("channel",_channelName);

        writeRead.writeNumberOfMessage(numOfChats+1,"channel",_channelName);
    }
    return result;
    }
    return OFFLINE;
}

int Request::getUserChats(QString _token,QString _dst, Date _date)
{
    QString url;
    //***url***
    url+=baseUrl+"getuserchats?token="+_token+"&dst="+_dst;
    if(_date.getRowDate()==Date().getRowDate());
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    }


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of message with dst user***********
        int numberOfChats=Request::calculate(messageResult);
        MyFile write;
        write.writeNumberOfMessage(numberOfChats,"private",_dst);
        write.writeMessages(numberOfChats,"private",_dst,jsonObj);

    }
     return result;
    }
    return OFFLINE;
}

int Request::getGroupChats(QString _token, QString _dst, Date _date)
{
    QString url;
    //***url***
    url+=baseUrl+"getgroupchats?token="+_token+"&dst="+_dst;
    if(_date.getRowDate()==Date().getRowDate());
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    }


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
    QString messageResult=jsonObj.value("message").toString();
    //*******calculate number of message with dst user***********
    int numberOfChats=Request::calculate(messageResult);
    MyFile write;
    write.writeNumberOfMessage(numberOfChats,"group",_dst);

    write.writeMessages(numberOfChats,"group",_dst,jsonObj);
    }
    return result;
    }
    return OFFLINE;

}

int Request::getChannelChats(QString _token, QString _dst, Date _date)
{
    QString url;
    //***url***
    url+=baseUrl+"getchannelchats?token="+_token+"&dst="+_dst;
    if(_date.getRowDate()==Date().getRowDate());
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    }


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
    QString messageResult=jsonObj.value("message").toString();
    //*******calculate number of message with dst user***********
    int numberOfChats=Request::calculate(messageResult);
    MyFile write;
    write.writeNumberOfMessage(numberOfChats,"channel",_dst);
    write.writeMessages(numberOfChats,"channel",_dst,jsonObj);
    }
     return result;
    }
    return OFFLINE;

}

