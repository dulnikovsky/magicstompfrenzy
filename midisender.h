#ifndef MIDISENDER_H
#define MIDISENDER_H

#include <QObject>

typedef struct _snd_seq snd_seq_t;

class MidiSender : public QObject
{
    Q_OBJECT
public:
    explicit MidiSender(snd_seq_t *handle, int outport, QObject *parent = nullptr);

    bool event(QEvent *);

signals:

public slots:

private:
    snd_seq_t *handle;
    int outport;

};

#endif // MIDISENDER_H
