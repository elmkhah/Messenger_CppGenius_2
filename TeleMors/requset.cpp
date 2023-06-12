#include "requset.h"
#include<QCoreApplication>
Requset::Requset()
{
    baseUrl="http://api.barafardayebehtar.ml:8080/";
}

int Requset::login(User &_user)
{
    QString url;
    url+=baseUrl+"login?username="+_user.getUsername()+"&password="+_user.getPassword();

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
 QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
            QByteArray data = reply->readAll();
            qDebug() << "Response:" << data;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString result=jsonObj.value("code").toString();
            if(result=="200"){
                QString _token=jsonObj.value("token").toString();
                _user.setToken(_token);
                QString fileName = "islogin.txt";
                QDir dir(QDir::currentPath());
                dir.mkdir("information");
                QString infoPath(QDir::currentPath()+"/information/");
                QFile file(infoPath+"isLogin.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream out(&file);
                    out<<"1";
            }
                    file.close();

                return 200;
            }
            return 0;


}


