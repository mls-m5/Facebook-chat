#include <QtGui/QtGui>
#include <QtWidgets/qtextedit.h>
#include <QtWebKit/QtWebKit>
#include <QtCore/qthread.h>
#include <QtCore/qsettings.h>
#include <QtWebKitWidgets/QtWebKitWidgets>

QWebView *pubView;


const QString code("document.getElementById('pagelet_bluebar').style.display = 'none'; \
document.getElementsByClassName('ego_section')[0].style.display = 'none';");

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

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QWebView view;

    pubView = &view;

    view.show();
    view.setUrl(QUrl("https://www.facebook.com/messages"));

	timer qtim(&app);
	qtim.start(1000);
    auto ret = app.exec();
    app.quit();
    return ret;
}
