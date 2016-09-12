#include <QtGui/QtGui>
#include <QtWidgets/qtextedit.h>
#include <QtWebKit/QtWebKit>
#include <QtCore/qthread.h>
#include <QtCore/qsettings.h>
#include <QtWebKitWidgets/QtWebKitWidgets>

QWebView *pubView;


class PersistentCookieJar : public QNetworkCookieJar {
public:
    PersistentCookieJar(QObject *parent) : QNetworkCookieJar(parent) { load(); }
    ~PersistentCookieJar() { save(); }

public:
    void save()
    {
        QList<QNetworkCookie> list = allCookies();
        QByteArray data;
        foreach (QNetworkCookie cookie, list) {
            if (!cookie.isSessionCookie()) {
                data.append(cookie.toRawForm());
                data.append("\n");
            }
        }
        QSettings settings;
        settings.setValue("Cookies",data);
    }

    void load()
    {
        QSettings settings;
        QByteArray data = settings.value("Cookies").toByteArray();
        setAllCookies(QNetworkCookie::parseCookies(data));
    }
};

const QString code(R"tag(

document.getElementById('pagelet_bluebar').style.display = 'none';
document.getElementsByClassName('ego_section')[0].style.display = 'none';

)tag");

//------------------Class to handle hiding of the blue bar------------

class timer : public QTimer{
public:

	timer(QApplication *a){
	}

	QVariant runScript(const QString& scriptSource){
		return pubView->page()->mainFrame()->evaluateJavaScript(scriptSource);
	}

	void feedbackPrint(const QString &text, int messageId){
		static int lastId;
		if (messageId == lastId) return;
		lastId = messageId;
	}


protected:
    void timerEvent(QTimerEvent *){
    	auto apa = runScript("document.readyState");
    	auto title = runScript("document.title").toString();
    	pubView->setWindowTitle(title);
    	if(apa.toString().compare("complete") == 0 ){

    		if (runScript("document.getElementById('stream_pagelet') != null") == "true") {
    		    pubView->setUrl(QUrl("https://www.facebook.com/messages"));
    		}
    		else {
    			runScript(code);
    		}
    	}
    }

private:
};


void setPersistance(QWebView *view) {
    auto jar = new PersistentCookieJar(view);
    view->page()->networkAccessManager()->setCookieJar(jar);  // the jar is reparented to the page
    jar->setParent(view);  // reparent to main widget to avoid destruction together with the page
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QWebView view;

    pubView = &view;
    setPersistance(&view);
    view.show();
    view.setUrl(QUrl("https://www.messenger.com"));

	timer qtim(&app);
	qtim.start(1000);
    auto ret = app.exec();
    qtim.stop();
    app.quit();
    return ret;
}
