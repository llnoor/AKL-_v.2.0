#include <QDebug>
#include <QLibrary>

int main() {
    static QString suffix = "";
#ifdef QT_DEBUG
    suffix = "d";
#endif

    static const QString LIB_NAME = "MyLib" + suffix;

    QLibrary lib( LIB_NAME );
    if( !lib.load() ) {
        qDebug() << "Loading failed!";
        return 1;
    }

    typedef void ( *InputTest )( const char* const );
    InputTest inputTest = ( InputTest ) lib.resolve( "inputTest" );
    if( inputTest ) {
        inputTest( "Hello to MyLib!" );
    }

    typedef const char* ( *OutputTest )();
    OutputTest outputTest = ( OutputTest ) lib.resolve( "outputTest" );
    if( outputTest ) {
        qDebug() << outputTest();
    }

    return 0;
}
