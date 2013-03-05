%modules = ( # path to module name map
    "QtWebKit" => "$basedir",
    "QtWebKitWidgets" => "$basedir",
    "QtWebKit1Quick" => "$basedir"
);
%moduleheaders = ( # restrict the module headers to those found in relative path
    "QtWebKit" => "WebKit/qt/Api;WebKit2/UIProcess/API/qt",
    "QtWebKitWidgets" => "WebKit/qt/WidgetApi",
    "QtWebKit1Quick" => "WebKit/qt/QuickApi",
);
%classnames = (
);
@ignore_for_master_contents = ( "qwebscriptworld.h", "testwindow.h", "util.h", "bytearraytestdata.h" );

# Module dependencies.
# Every module that is required to build this module should have one entry.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - any git symbolic ref resolvable from the module's repository (e.g. "refs/heads/master" to track master branch)
#
%dependencies = (
    "qtbase" => "refs/heads/dev",
    "qtxmlpatterns" => "refs/heads/dev",
    "qtdeclarative" => "refs/heads/dev",
    "qtjsbackend" => "refs/heads/dev",
);
