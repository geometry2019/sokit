#include <QTabWidget>
#include <QShortcut>
#include <QFontDatabase>

#include "toolkit.h"
#include "setting.h"
#include "clientform.h"
#include "serverform.h"
#include "transferform.h"
#include "notepadform.h"
#include "helpform.h"
#include "httpform.h"
#include "main.h"

#define SET_KEY_FTNM "/font/name"
#define SET_KEY_FTSZ "/font/size"

#define SET_KEY_LANG "/lang"
#define SET_VAL_LANG "sokit"
#define SET_VAL_LANX ".lan"

Sokit::Sokit(int& argc, char** argv)
:QApplication(argc,argv)
{

}

Sokit::~Sokit()
{
}

void Sokit::show()
{
	m_wnd.show();
}

void Sokit::close()
{
	m_wnd.close();
}

void Sokit::initDefaultActionsName()
{
	translate("QLineEdit", "&Undo");
	translate("QLineEdit", "&Redo");
	translate("QLineEdit", "Cu&t");
	translate("QLineEdit", "&Copy");
	translate("QLineEdit", "&Paste");
	translate("QLineEdit", "Delete");
	translate("QLineEdit", "Select All");

	translate("QTextControl", "&Undo");
	translate("QTextControl", "&Redo");
	translate("QTextControl", "Cu&t");
	translate("QTextControl", "&Copy");
	translate("QTextControl", "&Paste");
	translate("QTextControl", "Delete");
	translate("QTextControl", "Select All");
}


void Sokit::initFont()
{

}

bool Sokit::initUI()
{
	initFont();

	HelpForm* h = new HelpForm(&m_wnd, Qt::WindowCloseButtonHint);

	QShortcut* k = new QShortcut(QKeySequence(Qt::Key_F1), &m_wnd);
	QShortcut* t = new QShortcut(QKeySequence(Qt::Key_F10), &m_wnd);
    connect(k, SIGNAL(activated()), h, SLOT(exec()));
	connect(t, SIGNAL(activated()), this, SLOT(ontop()));

    m_wnd.setWindowTitle("Sokit 键入F1以打开帮助");
	m_wnd.setWindowIcon(QIcon(":/sokit.png"));

	QWidget* pnl = new QWidget(&m_wnd);
	m_wnd.setCentralWidget(pnl);

	BaseForm* server = new ServerForm();
	BaseForm* transf = new TransferForm();
	BaseForm* client = new ClientForm();
    BaseForm* httpf=new httpform();
	NotepadForm* npd = new NotepadForm();

	QTabWidget* tab = new QTabWidget(pnl);
	tab->addTab(server, server->windowTitle());
    tab->addTab(client, client->windowTitle());
	tab->addTab(transf, transf->windowTitle());
    tab->addTab(httpf,httpf->windowTitle());

	tab->addTab(npd, npd->windowTitle());
	tab->setCurrentIndex(0);

	QLayout* lay = new QVBoxLayout(pnl);
	lay->setSpacing(5);
	lay->setContentsMargins(5, 5, 5, 5);
	lay->addWidget(tab);

	return server->init() && transf->init() &&
		client->init() && npd->init();
}

void Sokit::ontop()
{
	Qt::WindowFlags f = m_wnd.windowFlags();
	if (f & Qt::WindowStaysOnTopHint)
		f &= ~Qt::WindowStaysOnTopHint;
	else
		f |= Qt::WindowStaysOnTopHint;

	m_wnd.setWindowFlags(f);
	m_wnd.show();
}

int main(int argc, char *argv[])
{
	Sokit a(argc, argv);

	if (a.initUI())
		a.show();
	else
		a.close();
	
	return a.exec();
}
