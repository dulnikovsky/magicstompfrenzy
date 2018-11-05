#include "mainwindow.h"
#include "midiapplication.h"

int main(int argc, char *argv[])
{
    MidiApplication a(argc, argv);
    a.setApplicationName("MagicstompFrenzy");
    a.setOrganizationName("Robert Vetter");
    a.setOrganizationDomain("www.robertvetter.com");
    a.setApplicationVersion("0.90");

    MainWindow w( a.ReadablePortsModel(), a.WritablePortsModel());

    QObject::connect( &a, SIGNAL(midiEventReceived(MidiEvent *)), &w, SLOT(midiEvent(MidiEvent*)));
    QObject::connect( &w, SIGNAL(sendMidiEvent(MidiEvent*)), &a, SLOT(sendMidiEvent(MidiEvent*)));

    QObject::connect( &w, SIGNAL(readableMidiPortSelected(MidiClientPortId)), &a, SLOT(connectToReadablePort( MidiClientPortId)));
    QObject::connect( &w, SIGNAL(writableMidiPortSelected(MidiClientPortId)), &a, SLOT(connectToWritablePort( MidiClientPortId)));

    w.show();

    return a.exec();
}
