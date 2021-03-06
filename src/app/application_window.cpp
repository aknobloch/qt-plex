#include "application_window.h"

#include <QDesktopWidget>
#include <QInputDialog>
#include <QMenuBar>
#include <QWebEngineView>
#include <Qt>
#include <QtWebEngine/QtWebEngine>

#include "constants.h"
#include "file_loader.h"
#include "first_time_setup_widget.h"
#include "key_event_controller.h"
#include "plex_web_page.h"
#include "settings_dialog.h"

ApplicationWindow::ApplicationWindow() {
  // Sets the initial size to fill screen
  resize(QDesktopWidget().availableGeometry(this).size());

  initializeMenuBar();
  initializeCentralWidget();
}

ApplicationWindow::~ApplicationWindow() = default;

void ApplicationWindow::initializeMenuBar() {
  std::unique_ptr<QMenu> file = std::make_unique<QMenu>(kAppName + " Menu");
  file->addAction("Settings", this, &ApplicationWindow::showSettingsDialog);

  menuBar()->setStyleSheet(FileLoader::loadCSSByName(kCSSFileTitleBar));
  menuBar()->addMenu(file.release());
}

void ApplicationWindow::initializeCentralWidget() {
  QSettings settings;
  QString server_address = settings.value(kServerAddressKey).toString();

  // If server address setting has not yet been defined,
  // immediately show the help window to configure.
  if (server_address.isNull()) {
    setHelpWindow();
  } else {
    initializeWebEngineView(server_address);
  }
}

void ApplicationWindow::setHelpWindow() {
  std::unique_ptr<FirstTimeSetupWidget> help_view =
      std::make_unique<FirstTimeSetupWidget>();
  connect(help_view.get(), &FirstTimeSetupWidget::notifyConfigButtonPressed,
          this, &ApplicationWindow::showSettingsDialog);

  setCentralWidget(help_view.release());
}

void ApplicationWindow::initializeWebEngineView(QString server_address) {
  auto page = std::make_unique<PlexWebPage>();
  page->setUrl(QUrl(server_address));

  web_engine_view_ = std::make_unique<QWebEngineView>();
  web_engine_view_->setPage(page.release());

  setCentralWidget(web_engine_view_.get());
}

void ApplicationWindow::show() {
  if (showingHelpScreen()) {
    showNormal();
  } else {
    showMaximized();
  }
}

void ApplicationWindow::showSettingsDialog() {
  QSettings settings;
  QString old_server_address = settings.value(kServerAddressKey).toString();

  SettingsDialog options;
  options.exec();

  QString new_server_address = settings.value(kServerAddressKey).toString();
  bool user_changed_server_address =
      old_server_address.compare(new_server_address) != 0;

  if (showingHelpScreen() || user_changed_server_address) {
    initializeCentralWidget();
  }
}

bool ApplicationWindow::showingHelpScreen() {
  return dynamic_cast<FirstTimeSetupWidget *>(centralWidget());
}
