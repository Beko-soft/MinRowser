#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QTabWidget>
#include <QTabBar>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QKeySequence>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QStyle>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineHistory>
#include <QCompleter>
#include <QStringListModel>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include <QSplitter>
#include <QStackedWidget>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QContextMenuEvent>
#include <QScrollArea>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QScreen>

// ─── Color Palette (Grayscale) ────────────────────────────────────────────────
static const QString BG_DARK      = "#1c1c1c";
static const QString BG_PANEL     = "#222222";
static const QString BG_TOOLBAR   = "#242424";
static const QString BG_INPUT     = "#2a2a2a";
static const QString BG_HOVER     = "#333333";
static const QString BG_ACTIVE    = "#3a3a3a";
static const QString ACCENT       = "#8c8c8c";
static const QString ACCENT_GLOW  = "#5a5a5a";
static const QString ACCENT_LIGHT = "#aaaaaa";
static const QString TEXT_PRIMARY = "#e6e6e6";
static const QString TEXT_MUTED   = "#9a9a9a";
static const QString TEXT_DIM     = "#5f5f5f";
static const QString SUCCESS      = "#bdbdbd";
static const QString WARNING_CLR  = "#bdbdbd";
static const QString DANGER       = "#bdbdbd";
static const QString BORDER       = "#3a3a3a";

// ─── Layout Constants ─────────────────────────────────────────────────────────
static const int TOOLBAR_HEIGHT = 40;
static const int NAV_BTN_SIZE   = 30;
static const int URLBAR_HEIGHT  = 30;

static const QString GLOBAL_STYLE = R"(
* { font-family: 'Segoe UI', system-ui, sans-serif; }
QMainWindow { background: )" + BG_DARK + R"(; }
QWidget#centralWidget { background: )" + BG_DARK + R"(; }
QTabWidget::pane { border: none; background: )" + BG_DARK + R"(; }
QTabBar { background: )" + BG_TOOLBAR + R"(; }
QTabBar::tab {
    background: )" + BG_PANEL + R"(;
    color: )" + TEXT_MUTED + R"(;
    padding: 6px 14px;
    margin-right: 2px;
    margin-top: 4px;
    border-radius: 4px 4px 0 0;
    min-width: 120px;
    max-width: 220px;
    height: 22px;
    font-size: 12px;
    border: 1px solid )" + BORDER + R"(;
    border-bottom: none;
}
QTabBar::tab:selected { background: )" + BG_ACTIVE + R"(; color: )" + TEXT_PRIMARY + R"(; border-color: )" + ACCENT + R"(; }
QTabBar::tab:hover:!selected { background: )" + BG_HOVER + R"(; color: )" + TEXT_PRIMARY + R"(; }
QTabBar::close-button { subcontrol-position: right; }
QToolBar {
    background: )" + BG_TOOLBAR + R"(;
    border: none;
    border-bottom: 1px solid )" + BORDER + R"(;
    padding: 0px 8px;
    spacing: 6px;
    min-height: )" + QString::number(TOOLBAR_HEIGHT) + R"(px;
    max-height: )" + QString::number(TOOLBAR_HEIGHT) + R"(px;
}
QLineEdit#urlBar {
    background: )" + BG_INPUT + R"(;
    color: )" + TEXT_PRIMARY + R"(;
    border: 1px solid )" + BORDER + R"(;
    border-radius: 6px;
    padding: 0px 12px 0px 32px;
    font-size: 13px;
    selection-background-color: )" + ACCENT_GLOW + R"(;
}
QLineEdit#urlBar:focus { border-color: )" + ACCENT + R"(; background: )" + BG_HOVER + R"(; }
QLineEdit#urlBar:hover:!focus { border-color: )" + TEXT_DIM + R"(; }
QPushButton#navBtn {
    background: transparent;
    color: )" + TEXT_MUTED + R"(;
    border: none;
    border-radius: 6px;
    padding: 0px;
    font-size: 14px;
    font-weight: bold;
}
QPushButton#navBtn:hover { background: )" + BG_HOVER + R"(; color: )" + TEXT_PRIMARY + R"(; }
QPushButton#navBtn:pressed { background: )" + BG_ACTIVE + R"(; }
QPushButton#navBtn:disabled { color: )" + TEXT_DIM + R"(; }
QPushButton#accentBtn {
    background: )" + ACCENT_GLOW + R"(;
    color: )" + TEXT_PRIMARY + R"(;
    border: none;
    border-radius: 6px;
    padding: 0px;
    font-size: 14px;
    font-weight: 600;
}
QPushButton#accentBtn:hover { background: )" + ACCENT + R"(; }
QPushButton#accentBtn:pressed { background: )" + ACCENT_LIGHT + R"(; }
QProgressBar { background: )" + BG_PANEL + R"(; border: none; height: 2px; max-height: 2px; border-radius: 0px; }
QProgressBar::chunk { background: )" + ACCENT + R"(; border-radius: 0px; }
QStatusBar { background: )" + BG_TOOLBAR + R"(; color: )" + TEXT_MUTED + R"(; border-top: 1px solid )" + BORDER + R"(; font-size: 11px; padding: 2px 6px; }
QStatusBar::item { border: none; }
QScrollBar:vertical { background: )" + BG_PANEL + R"(; width: 8px; border-radius: 4px; margin: 0px; }
QScrollBar::handle:vertical { background: )" + TEXT_DIM + R"(; border-radius: 4px; min-height: 30px; }
QScrollBar::handle:vertical:hover { background: )" + TEXT_MUTED + R"(; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }
QScrollBar:horizontal { background: )" + BG_PANEL + R"(; height: 8px; border-radius: 4px; margin: 0px; }
QScrollBar::handle:horizontal { background: )" + TEXT_DIM + R"(; border-radius: 4px; min-width: 30px; }
QScrollBar::handle:horizontal:hover { background: )" + TEXT_MUTED + R"(; }
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0px; }
QMenu { background: )" + BG_PANEL + R"(; color: )" + TEXT_PRIMARY + R"(; border: 1px solid )" + BORDER + R"(; border-radius: 6px; padding: 4px; font-size: 13px; }
QMenu::item { padding: 6px 20px 6px 14px; border-radius: 4px; }
QMenu::item:selected { background: )" + BG_HOVER + R"(; color: )" + TEXT_PRIMARY + R"(; }
QMenu::separator { height: 1px; background: )" + BORDER + R"(; margin: 3px 8px; }
QToolTip { background: )" + BG_PANEL + R"(; color: )" + TEXT_PRIMARY + R"(; border: 1px solid )" + BORDER + R"(; border-radius: 4px; padding: 4px 8px; font-size: 12px; }
QLabel { color: )" + TEXT_PRIMARY + R"(; }
)";

// ─── Sınıf Tanımları (Declarations) ───────────────────────────────────────────

class BrowserView : public QWebEngineView {
    Q_OBJECT
public:
    explicit BrowserView(QWidget* parent = nullptr);
    QWebEnginePage* webPage() const { return page(); }
protected:
    QWebEngineView* createWindow(QWebEnginePage::WebWindowType type) override;
signals:
    void newWindowRequested();
};

class UrlBar : public QLineEdit {
    Q_OBJECT
public:
    explicit UrlBar(QWidget* parent = nullptr);
    void setUrl(const QUrl& url);
    void addToHistory(const QString& url);
    void updateSecureIndicator(bool secure);
protected:
    void focusInEvent(QFocusEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
private:
    QCompleter* m_completer;
    QStringListModel* m_model;
    QStringList       m_history;
    QLabel* m_secureLabel;
};

struct TabData {
    BrowserView* view;
    UrlBar* urlBar;
    QProgressBar* progress;
    QString       title;
    QIcon         favicon;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
private slots:
    void createTab(const QString& url = QString());
    void showNewTabPage(BrowserView* view);
    void onUrlEntered();
    void navigate(const QString& input);
    void goBack();
    void goForward();
    void reloadOrStop();
    void onTabChanged(int idx);
    void closeTab(int idx);
    void updateNavButtons();
    void showMenu();
    void findInPage();
    void savePage();
    BrowserView* currentView() const;
    int indexOfView(BrowserView* view) const;
private:
    QTabWidget* m_tabs;
    QToolBar* m_toolbar;
    UrlBar* m_urlBar;
    QPushButton* m_backBtn;
    QPushButton* m_fwdBtn;
    QPushButton* m_reloadBtn;
    QPushButton* m_homeBtn;
    QProgressBar* m_globalProgress;
    QLabel* m_statusLabel;
    QMap<int, TabData> m_tabData;
};

// ─── CRITICAL: MOC Dosyasının Dahil Edildiği Yer ─────────────────────────────────
// Bu satırın burada olması, yukarıdaki 3 sınıfın da vtable yapısını kusursuz bağlar.
#include "browser.moc"

// ─── Sınıf Metotlarının Gövdeleri (Implementations) ───────────────────────────

// BrowserView Impl
// Kaynak tüketimini azaltmak için WebGL / hızlandırılmış 2D canvas ve eklenti
// desteği kapatıldı; bu özellikler her sekmede ekstra GPU/CPU/RAM yükü oluşturur
// ve normal bir gezinti tarayıcısı için zorunlu değildir.
BrowserView::BrowserView(QWidget* parent) : QWebEngineView(parent) {
    auto* p = new QWebEnginePage(QWebEngineProfile::defaultProfile(), this);
    setPage(p);
    auto* settings = p->settings();
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    settings->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    settings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, false);
    settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebEngineSettings::WebGLEnabled, false);
    settings->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, false);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, false);
}
QWebEngineView* BrowserView::createWindow(QWebEnginePage::WebWindowType) {
    emit newWindowRequested();
    return nullptr;
}

// UrlBar Impl
UrlBar::UrlBar(QWidget* parent) : QLineEdit(parent) {
    setObjectName("urlBar");
    setPlaceholderText("Search or enter address...");
    setClearButtonEnabled(true);
    setFixedHeight(URLBAR_HEIGHT);
    setTextMargins(0, 0, 0, 0);
    m_completer = new QCompleter(this);
    m_model = new QStringListModel(this);
    m_completer->setModel(m_model);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setFilterMode(Qt::MatchContains);
    setCompleter(m_completer);
    m_secureLabel = new QLabel(this);
    m_secureLabel->setFixedSize(16, 16);
    m_secureLabel->move(10, (height() - 16) / 2);
    updateSecureIndicator(false);
}
void UrlBar::setUrl(const QUrl& url) {
    if (!hasFocus()) {
        setText(url.toString());
        updateSecureIndicator(url.scheme() == "https");
    }
}
void UrlBar::addToHistory(const QString& url) {
    if (!url.isEmpty() && !m_history.contains(url)) {
        m_history.prepend(url);
        if (m_history.size() > 500) m_history.removeLast();
        m_model->setStringList(m_history);
    }
}
void UrlBar::updateSecureIndicator(bool secure) {
    QPixmap pm(16, 16);
    pm.fill(Qt::transparent);
    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing);
    QColor c = secure ? QColor(TEXT_PRIMARY) : QColor(TEXT_DIM);
    p.setPen(QPen(c, 1.5));
    p.drawRoundedRect(3, 7, 10, 7, 2, 2);
    p.drawArc(5, 2, 6, 8, 0, 180 * 16);
    m_secureLabel->setPixmap(pm);
}
void UrlBar::focusInEvent(QFocusEvent* e) { QLineEdit::focusInEvent(e); selectAll(); }
void UrlBar::resizeEvent(QResizeEvent* e) { QLineEdit::resizeEvent(e); m_secureLabel->move(10, (height() - 16) / 2); }

// MainWindow Impl
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Browser");
    resize(1280, 800);
    setMinimumSize(800, 500);
    setAttribute(Qt::WA_DeleteOnClose);

    auto* central = new QWidget(this);
    central->setObjectName("centralWidget");
    setCentralWidget(central);

    auto* rootLayout = new QVBoxLayout(central);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    m_toolbar = new QToolBar(this);
    m_toolbar->setMovable(false);
    m_toolbar->setFloatable(false);
    m_toolbar->setContextMenuPolicy(Qt::PreventContextMenu);
    m_toolbar->setFixedHeight(TOOLBAR_HEIGHT);
    m_toolbar->setIconSize(QSize(16, 16));
    rootLayout->addWidget(m_toolbar);

    auto makeNavBtn = [&](const QString& icon, const QString& tip, const QString& objName) {
        auto* btn = new QPushButton(icon, m_toolbar);
        btn->setObjectName(objName);
        btn->setToolTip(tip);
        btn->setFixedSize(NAV_BTN_SIZE, NAV_BTN_SIZE);
        btn->setCursor(Qt::PointingHandCursor);
        return btn;
    };

    m_backBtn    = makeNavBtn("<",  "Back (Alt+Left)",    "navBtn");
    m_fwdBtn     = makeNavBtn(">",  "Forward (Alt+Right)", "navBtn");
    m_reloadBtn  = makeNavBtn("R",  "Reload (F5)",          "navBtn");
    m_homeBtn    = makeNavBtn("H",  "Home",                 "navBtn");

    auto* navContainer = new QWidget(m_toolbar);
    auto* navLayout = new QHBoxLayout(navContainer);
    navLayout->setContentsMargins(0, 0, 0, 0);
    navLayout->setSpacing(4);
    navLayout->addWidget(m_backBtn);
    navLayout->addWidget(m_fwdBtn);
    navLayout->addWidget(m_reloadBtn);
    navLayout->addWidget(m_homeBtn);
    m_toolbar->addWidget(navContainer);

    auto* urlContainer = new QWidget(m_toolbar);
    auto* urlLayout    = new QHBoxLayout(urlContainer);
    urlLayout->setContentsMargins(8, 0, 8, 0);
    urlLayout->setSpacing(0);

    m_urlBar = new UrlBar(urlContainer);
    urlLayout->addWidget(m_urlBar);
    urlContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_toolbar->addWidget(urlContainer);

    auto* newTabBtn = new QPushButton("+", m_toolbar);
    newTabBtn->setObjectName("accentBtn");
    newTabBtn->setToolTip("New Tab (Ctrl+T)");
    newTabBtn->setFixedSize(NAV_BTN_SIZE, NAV_BTN_SIZE);
    newTabBtn->setCursor(Qt::PointingHandCursor);
    m_toolbar->addWidget(newTabBtn);

    auto* menuBtn = new QPushButton(":::", m_toolbar);
    menuBtn->setObjectName("navBtn");
    menuBtn->setToolTip("Menu");
    menuBtn->setFixedSize(NAV_BTN_SIZE, NAV_BTN_SIZE);
    menuBtn->setCursor(Qt::PointingHandCursor);
    m_toolbar->addWidget(menuBtn);

    m_globalProgress = new QProgressBar(this);
    m_globalProgress->setRange(0, 100);
    m_globalProgress->setValue(0);
    m_globalProgress->setFixedHeight(2);
    m_globalProgress->setTextVisible(false);
    m_globalProgress->hide();
    rootLayout->addWidget(m_globalProgress);

    m_tabs = new QTabWidget(this);
    m_tabs->setTabsClosable(true);
    m_tabs->setMovable(true);
    m_tabs->setDocumentMode(true);
    m_tabs->setElideMode(Qt::ElideRight);
    rootLayout->addWidget(m_tabs, 1);

    m_statusLabel = new QLabel(this);
    statusBar()->addWidget(m_statusLabel, 1);
    statusBar()->setSizeGripEnabled(false);
    statusBar()->setFixedHeight(22);

    connect(m_backBtn,   &QPushButton::clicked, this, &MainWindow::goBack);
    connect(m_fwdBtn,    &QPushButton::clicked, this, &MainWindow::goForward);
    connect(m_reloadBtn, &QPushButton::clicked, this, &MainWindow::reloadOrStop);
    connect(m_homeBtn,   &QPushButton::clicked, this, [this]{ navigate("https://www.google.com"); });
    connect(newTabBtn,   &QPushButton::clicked, this, [this]{ createTab(); });
    connect(m_urlBar,    &QLineEdit::returnPressed, this, &MainWindow::onUrlEntered);
    connect(m_tabs, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(m_tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(menuBtn, &QPushButton::clicked, this, &MainWindow::showMenu);

    new QShortcut(QKeySequence("Ctrl+T"),     this, [this]{ createTab(); });
    new QShortcut(QKeySequence("Ctrl+W"),     this, [this]{ closeTab(m_tabs->currentIndex()); });
    new QShortcut(QKeySequence("Ctrl+L"),     this, [this]{ m_urlBar->selectAll(); m_urlBar->setFocus(); });
    new QShortcut(QKeySequence("F5"),         this, this, &MainWindow::reloadOrStop);
    new QShortcut(QKeySequence("Ctrl+R"),     this, this, &MainWindow::reloadOrStop);
    new QShortcut(QKeySequence("Alt+Left"),   this, this, &MainWindow::goBack);
    new QShortcut(QKeySequence("Alt+Right"),  this, this, &MainWindow::goForward);
    new QShortcut(QKeySequence("Ctrl+Tab"),   this, [this]{
        if (m_tabs->count() < 2) return;
        int next = (m_tabs->currentIndex() + 1) % m_tabs->count();
        m_tabs->setCurrentIndex(next);
    });
    new QShortcut(QKeySequence("Ctrl+Shift+Tab"), this, [this]{
        if (m_tabs->count() < 2) return;
        int prev = (m_tabs->currentIndex() - 1 + m_tabs->count()) % m_tabs->count();
        m_tabs->setCurrentIndex(prev);
    });
    new QShortcut(QKeySequence("Ctrl+F"),    this, [this]{ findInPage(); });
    new QShortcut(QKeySequence("Escape"),    this, [this]{ if (auto* v = currentView()) v->stop(); });

    for (int i = 1; i <= 8; ++i) {
        int idx = i - 1;
        new QShortcut(QKeySequence(QKeyCombination(Qt::CTRL, static_cast<Qt::Key>(Qt::Key_0 + i))), this,
                      [this, idx]{ if (idx < m_tabs->count()) m_tabs->setCurrentIndex(idx); });
    }
    new QShortcut(QKeySequence("Ctrl+9"), this, [this]{ if (m_tabs->count() > 0) m_tabs->setCurrentIndex(m_tabs->count() - 1); });

    createTab("https://www.google.com");
}

void MainWindow::createTab(const QString& url) {
    auto* view     = new BrowserView(this);
    auto* progress = new QProgressBar();
    progress->setRange(0, 100);
    progress->setFixedHeight(2);
    progress->setTextVisible(false);
    progress->hide();

    auto* container = new QWidget();
    auto* vl        = new QVBoxLayout(container);
    vl->setContentsMargins(0, 0, 0, 0);
    vl->setSpacing(0);
    vl->addWidget(progress);
    vl->addWidget(view, 1);

    int idx = m_tabs->addTab(container, "New Tab");
    m_tabs->setCurrentIndex(idx);

    TabData td{ view, m_urlBar, progress, "New Tab", QIcon() };
    m_tabData.insert(idx, td);

    connect(view, &QWebEngineView::titleChanged, this, [this, view](const QString& t){
        int i = indexOfView(view);
        if (i < 0) return;
        QString label = t.isEmpty() ? "New Tab" : t;
        m_tabs->setTabText(i, label.left(30));
        if (i == m_tabs->currentIndex()) setWindowTitle(label + " - Browser");
    });

    connect(view, &QWebEngineView::urlChanged, this, [this, view](const QUrl& u){
        if (view == currentView()) {
            m_urlBar->setUrl(u);
            m_urlBar->addToHistory(u.toString());
            updateNavButtons();
        }
    });

    connect(view, &QWebEngineView::loadStarted, this, [this, view, progress]{
        progress->show();
        if (view == currentView()) {
            m_reloadBtn->setText("X");
            m_reloadBtn->setToolTip("Stop");
            m_globalProgress->show();
        }
    });

    connect(view, &QWebEngineView::loadProgress, this, [this, view, progress](int val){
        progress->setValue(val);
        if (view == currentView()) m_globalProgress->setValue(val);
    });

    connect(view, &QWebEngineView::loadFinished, this, [this, view, progress](bool ok){
        progress->hide();
        progress->setValue(0);
        if (view == currentView()) {
            m_reloadBtn->setText("R");
            m_reloadBtn->setToolTip("Reload (F5)");
            m_globalProgress->hide();
            m_globalProgress->setValue(0);
            updateNavButtons();
            if (!ok) m_statusLabel->setText("Failed to load page");
            else m_statusLabel->clear();
        }
    });

    connect(view->page(), &QWebEnginePage::linkHovered, this, [this](const QString& url){ m_statusLabel->setText(url); });
    connect(view, &BrowserView::newWindowRequested, this, [this]{ createTab(); });
    connect(view, &QWebEngineView::iconChanged, this, [this, view](const QIcon& icon){
        int i = indexOfView(view);
        if (i >= 0) m_tabs->setTabIcon(i, icon);
    });

    if (!url.isEmpty()) view->load(QUrl::fromUserInput(url));
    else showNewTabPage(view);

    updateNavButtons();
}

void MainWindow::showNewTabPage(BrowserView* view) {
    QString html = R"(<!DOCTYPE html><html><head>
<meta charset="UTF-8">
<title>New Tab</title>
<style>
* { margin:0; padding:0; box-sizing:border-box; }
body {
    font-family: 'Segoe UI',system-ui,sans-serif;
    background: )" + BG_DARK + R"(;
    color: )" + TEXT_PRIMARY + R"(;
    display: flex; flex-direction: column;
    align-items: center; justify-content: center;
    height: 100vh; overflow: hidden;
}
.clock { font-size: 64px; font-weight: 300; letter-spacing: -1px; color: )" + TEXT_PRIMARY + R"(; margin-bottom: 6px; }
.date { font-size: 15px; color: )" + TEXT_MUTED + R"(; margin-bottom: 44px; letter-spacing: 0.5px; }
.search-wrap { position: relative; width: 520px; max-width: 86vw; }
.search-wrap input {
    width: 100%; padding: 12px 18px 12px 44px;
    background: )" + BG_INPUT + R"(;
    border: 1px solid )" + BORDER + R"(;
    border-radius: 8px;
    color: )" + TEXT_PRIMARY + R"(;
    font-size: 14px; outline: none;
    box-sizing: border-box;
}
.search-wrap input:focus { border-color: )" + ACCENT + R"(; background: )" + BG_HOVER + R"(; }
.search-icon { position: absolute; left: 15px; top: 50%; transform: translateY(-50%); color: )" + TEXT_MUTED + R"(; font-size: 16px; pointer-events: none; }
.shortcuts { display: flex; gap: 14px; margin-top: 36px; flex-wrap: wrap; justify-content: center; max-width: 560px; }
.shortcut {
    display: flex; flex-direction: column; align-items: center; gap: 8px;
    cursor: pointer; padding: 10px 12px; border-radius: 8px;
    text-decoration: none; color: )" + TEXT_MUTED + R"(;
    width: 76px;
}
.shortcut:hover { background: )" + BG_HOVER + R"(; color: )" + TEXT_PRIMARY + R"(; }
.shortcut .icon {
    width: 40px; height: 40px; border-radius: 8px;
    background: )" + BG_PANEL + R"(;
    display: flex; align-items: center; justify-content: center;
    font-size: 16px; font-weight: 600; border: 1px solid )" + BORDER + R"(;
    color: )" + TEXT_PRIMARY + R"(;
}
.shortcut .label { font-size: 11px; text-align: center; }
</style>
</head><body>
<div class="clock" id="clock">00:00</div>
<div class="date" id="date"></div>
<div class="search-wrap">
<span class="search-icon">&#9906;</span>
<input type="text" placeholder="Search Google or enter address"
onkeydown="if(event.key==='Enter'){var q=this.value;
    window.location=q.includes('.')?'https://'+q:'https://www.google.com/search?q='+encodeURIComponent(q);}">
</div>
<div class="shortcuts">
<a class="shortcut" href="https://google.com"><div class="icon">G</div><div class="label">Google</div></a>
<a class="shortcut" href="https://github.com"><div class="icon">Gh</div><div class="label">GitHub</div></a>
<a class="shortcut" href="https://youtube.com"><div class="icon">Yt</div><div class="label">YouTube</div></a>
<a class="shortcut" href="https://reddit.com"><div class="icon">R</div><div class="label">Reddit</div></a>
<a class="shortcut" href="https://wikipedia.org"><div class="icon">W</div><div class="label">Wikipedia</div></a>
</div>
<script>
function updateClock(){
    var now=new Date();
    var h=String(now.getHours()).padStart(2,'0');
    var m=String(now.getMinutes()).padStart(2,'0');
    document.getElementById('clock').textContent=h+':'+m;
    var days=['Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday'];
    var months=['January','February','March','April','May','June','July','August','September','October','November','December'];
    document.getElementById('date').textContent=days[now.getDay()]+', '+months[now.getMonth()]+' '+now.getDate();
}
updateClock(); setInterval(updateClock,30000);
</script>
</body></html>)";
    view->setHtml(html, QUrl("about:blank"));
}

void MainWindow::onUrlEntered() { navigate(m_urlBar->text().trimmed()); }

void MainWindow::navigate(const QString& input) {
    if (input.isEmpty()) return;
    QUrl url;
    if (input.startsWith("http://") || input.startsWith("https://") || input.startsWith("file://") || input.startsWith("about:") || input.startsWith("view-source:")) {
        url = QUrl(input);
    } else if (input.contains('.') && !input.contains(' ')) {
        url = QUrl("https://" + input);
    } else {
        url = QUrl("https://www.google.com/search?q=" + QUrl::toPercentEncoding(input));
    }
    if (auto* v = currentView()) v->load(url);
    m_urlBar->clearFocus();
}

void MainWindow::goBack() { if (auto* v = currentView()) v->back(); }
void MainWindow::goForward() { if (auto* v = currentView()) v->forward(); }
void MainWindow::reloadOrStop() {
    if (auto* v = currentView()) {
        if (m_reloadBtn->text() == "X") v->stop();
        else v->reload();
    }
}

void MainWindow::onTabChanged(int idx) {
    if (idx < 0 || !currentView()) return;
    auto* v = currentView();
    m_urlBar->setUrl(v->url());
    updateNavButtons();
    QString tabText = m_tabs->tabText(idx);
    setWindowTitle((tabText.isEmpty() ? "New Tab" : tabText) + " - Browser");
}

void MainWindow::closeTab(int idx) {
    if (idx < 0 || idx >= m_tabs->count()) return;
    if (m_tabs->count() <= 1) {
        QApplication::quit();
        return;
    }
    auto* w = m_tabs->widget(idx);
    m_tabData.remove(idx);
    m_tabs->removeTab(idx);
    w->deleteLater();
}

void MainWindow::updateNavButtons() {
    if (auto* v = currentView()) {
        m_backBtn->setEnabled(v->history()->canGoBack());
        m_fwdBtn->setEnabled(v->history()->canGoForward());
    } else {
        m_backBtn->setEnabled(false);
        m_fwdBtn->setEnabled(false);
    }
}

void MainWindow::showMenu() {
    QMenu menu(this);
    menu.addAction("New Tab", QKeySequence("Ctrl+T"), this, [this]{ createTab(); });
    menu.addAction("Reload", QKeySequence("F5"), this, &MainWindow::reloadOrStop);
    menu.addSeparator();
    menu.addAction("Find in Page", QKeySequence("Ctrl+F"), this, &MainWindow::findInPage);
    menu.addSeparator();
    menu.addAction("Save Page As...", this, &MainWindow::savePage);
    menu.addAction("Print...", this, [this]{
        if (auto* v = currentView()) v->page()->runJavaScript("window.print()");
    });
    menu.addSeparator();
    menu.addAction("Copy URL", this, [this]{
        if (auto* v = currentView()) QApplication::clipboard()->setText(v->url().toString());
    });
    menu.addAction("View Source", this, [this]{
        if (auto* v = currentView()) createTab("view-source:" + v->url().toString());
    });
    menu.addSeparator();
    menu.addAction("Quit", QKeySequence("Ctrl+Q"), this, &QApplication::quit);
    menu.exec(QCursor::pos());
}

void MainWindow::findInPage() {
    static QWidget* findBar = nullptr;
    static QLineEdit* findInput = nullptr;
    if (!findBar) {
        findBar = new QWidget(centralWidget());
        findBar->setStyleSheet("background:" + BG_PANEL + "; border-top: 1px solid " + BORDER + ";");
        findBar->setFixedHeight(34);
        auto* fl = new QHBoxLayout(findBar);
        fl->setContentsMargins(8, 4, 8, 4);
        fl->setSpacing(6);
        auto* lbl = new QLabel("Find:");
        lbl->setStyleSheet("color:" + TEXT_MUTED + "; font-size:12px;");
        findInput = new QLineEdit();
        findInput->setFixedHeight(24);
        findInput->setStyleSheet("background:" + BG_INPUT + "; color:" + TEXT_PRIMARY + "; border: 1px solid " + BORDER + "; border-radius:4px; padding: 0px 8px; font-size:12px;");
        findInput->setPlaceholderText("Search...");
        auto* closeBtn = new QPushButton("X");
        closeBtn->setStyleSheet("background:transparent; color:" + TEXT_MUTED + "; border:none; font-size:12px;");
        closeBtn->setFixedSize(22, 22);
        closeBtn->setCursor(Qt::PointingHandCursor);
        fl->addWidget(lbl);
        fl->addWidget(findInput, 1);
        fl->addWidget(closeBtn);

        auto* root = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
        if (root) root->insertWidget(root->count() - 1, findBar);

        connect(findInput, &QLineEdit::textChanged, this, [this](const QString& t){ if (auto* v = currentView()) v->findText(t); });
        connect(findInput, &QLineEdit::returnPressed, this, [this]{ if (auto* v = currentView()) v->findText(findInput->text()); });
        connect(closeBtn, &QPushButton::clicked, this, [this]{
            if (auto* v = currentView()) v->findText(QString());
            findInput->clear();
            findBar->hide();
        });
    }
    findBar->show();
    findInput->setFocus();
    findInput->selectAll();
}

void MainWindow::savePage() {
    if (auto* v = currentView()) {
        QString path = QFileDialog::getSaveFileName(this, "Save Page", QDir::homePath() + "/page.html", "HTML (*.html)");
        if (!path.isEmpty()) v->page()->save(path, QWebEngineDownloadRequest::CompleteHtmlSaveFormat);
    }
}

BrowserView* MainWindow::currentView() const {
    auto* w = m_tabs->currentWidget();
    if (!w) return nullptr;
    return w->findChild<BrowserView*>();
}

int MainWindow::indexOfView(BrowserView* view) const {
    for (int i = 0; i < m_tabs->count(); ++i) {
        if (m_tabs->widget(i)->findChild<BrowserView*>() == view) return i;
    }
    return -1;
}

// ─── Main ────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    QCoreApplication::setOrganizationName("Browser");
    QCoreApplication::setApplicationName("Browser");

    // Kaynak tüketimini düşürmek için: GPU rasterization kapalı, yazılım render
    // tercih ediliyor (özellikle düşük/orta seviye GPU'larda RAM ve VRAM
    // kullanımını azaltır). Sandbox açık bırakılmıştır (güvenlik için önerilir).
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS",
            "--disable-gpu-compositing --disable-software-rasterizer --disable-extensions --disable-background-timer-throttling");

    QApplication app(argc, argv);
    app.setStyleSheet(GLOBAL_STYLE);

    MainWindow w;
    w.show();

    return app.exec();
}
