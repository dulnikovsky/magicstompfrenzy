/****************************************************************************
**
** Copyright (C) 2018 Robert Vetter.
**
** This file is part of the MagicstompFrenzy - an editor for Yamaha Magicstomp
** effect processor
**
** THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
** ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
** IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
** PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version . The licenses are
** as published by the Free Software Foundation and appearing in the file LICENSE
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**/
#include "mainwindow.h"

#include <QCommandLineParser>

#include "midiportmodel.h"

int main(int argc, char *argv[])
{
    MidiApplication a(argc, argv);
    a.setApplicationName("MagicstompFrenzy");
    a.setOrganizationName("RobertVetter");
    a.setOrganizationDomain("www.robertvetter.com");
    a.setApplicationVersion("0.910");
    a.setWindowIcon(QIcon(":magicstomp.png"));

    MainWindow mw( a.ReadablePortsModel(), a.WritablePortsModel());

    QObject::connect( &a, SIGNAL(midiEventReceived(MidiEvent *)), &mw, SLOT(midiEvent(MidiEvent*)));

    /* Example command line for auto start:
     * --ignorepreferences --hideeditor --mwx 0 --mwy 0 --mwh 400 --mww 600 --smf /home/robert/MagicstompHoldsworthSounds.mid --findandconnectms 0 --connectmidiinport MS1x1
     */

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption hideEditorWindowOption(QStringList() << "hideeditor", "No editor");
    parser.addOption(hideEditorWindowOption);

    QCommandLineOption ignorePreferencesOption(QStringList() << "ignorepreferences", "No preferences");
    parser.addOption(ignorePreferencesOption);

    QCommandLineOption mwxOption(QStringList() << "mwx", "Main Window X", "0");
    parser.addOption(mwxOption);

    QCommandLineOption mwyOption(QStringList() << "mwy", "Main Window Y", "0");
    parser.addOption(mwyOption);

    QCommandLineOption mwwOption(QStringList() << "mww", "Main Window Width", "400");
    parser.addOption(mwwOption);

    QCommandLineOption mwhOption(QStringList() << "mwh", "Main Window Height", "400");
    parser.addOption(mwhOption);

    QCommandLineOption smfOption(QStringList() << "smf", "SMF with patches to import", "Filename");
    parser.addOption(smfOption);

    QCommandLineOption findandconnectMSOption(QStringList() << "findandconnectms", "index of the MS in the system", "index");
    parser.addOption(findandconnectMSOption);

    QCommandLineOption connectmidiInPortOption(QStringList() << "connectmidiinport", "Port Name", "name");
    parser.addOption(connectmidiInPortOption);

    parser.process(a);

    if(! parser.isSet(ignorePreferencesOption))
    {
        mw.restoreSettings();
    }
    if(parser.isSet(hideEditorWindowOption))
    {
        mw.hideEditor();
    }

    if(parser.isSet(mwxOption) && parser.isSet(mwyOption))
    {
        QString xStr = parser.value(mwxOption);
        QString yStr = parser.value(mwyOption);
        bool okx;
        bool oky;

        int x = xStr.toInt( &okx);
        int y = yStr.toInt( &oky);
        if( okx && oky)
            mw.move( x, y);
    }

    if(parser.isSet(mwwOption) && parser.isSet(mwhOption))
    {
        QString wStr = parser.value(mwhOption);
        QString hStr = parser.value(mwwOption);
        bool okw;
        bool okh;

        int w = wStr.toInt( &okw);
        int h = hStr.toInt( &okh);
        if( okw && okh)
            mw.resize( w, h);
    }

    if(parser.isSet(smfOption))
    {
        bool res;
        QString file = parser.value(smfOption);
        res = mw.importSMF( file , MainWindow::PatchListType::User);
        if ( ! res)
        {
            printf("Error opening file %s\n", file.toLocal8Bit().constData());
            exit(1);
        }
    }

    if(parser.isSet(findandconnectMSOption))
    {
        QString indexStr = parser.value(findandconnectMSOption);
        bool ok;
        int msindex = indexStr.toInt( &ok);
        int mscounter = 0;
        if(ok)
        {
            MidiPortModel *midiportmodel = a.ReadablePortsModel();
            for(int r = 0; r<midiportmodel->rowCount(); r++)
            {
                QString name = midiportmodel->data( midiportmodel->index(r, 0), Qt::DisplayRole ).toString();
                if(name.contains("UB99"))
                {
                    if( mscounter == msindex)
                    {
                        MidiClientPortId id = qvariant_cast<MidiClientPortId> (midiportmodel->data( midiportmodel->index(r, 0), MidiPortModel::ClientPortIdRole));
                        a.changeReadableMidiPortStatus( id, true);
                        break;
                    }
                    mscounter++;
                }
            }
            midiportmodel = a.WritablePortsModel();
            mscounter = 0;
            for(int r = 0; r<midiportmodel->rowCount(); r++)
            {
                QString name = midiportmodel->data( midiportmodel->index(r, 0), Qt::DisplayRole ).toString();
                if(name.contains("UB99"))
                {
                    if( mscounter == msindex)
                    {
                        MidiClientPortId id = qvariant_cast<MidiClientPortId> (midiportmodel->data( midiportmodel->index(r, 0), MidiPortModel::ClientPortIdRole));
                        a.changeWritebleMidiPortStatus( id, true);
                        break;
                    }
                    mscounter++;
                }
            }
        }
    }

    if(parser.isSet(connectmidiInPortOption))
    {
        QString portname = parser.value(connectmidiInPortOption);
        MidiPortModel *midiportmodel = a.ReadablePortsModel();
        for(int r = 0; r<midiportmodel->rowCount(); r++)
        {
            QString name = midiportmodel->data( midiportmodel->index(r, 0), Qt::DisplayRole ).toString();
            if(name.contains(portname))
            {
                MidiClientPortId id = qvariant_cast<MidiClientPortId> (midiportmodel->data( midiportmodel->index(r, 0), MidiPortModel::ClientPortIdRole));
                a.changeReadableMidiPortStatus( id, true);
                break;
            }
        }
    }


    mw.show();

    return a.exec();
}
