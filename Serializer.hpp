#ifndef SERIALIZER_HH
#define SERIALIZER_HH

#include <QString>
#include <QTextStream>

#include "NodeTypes.hpp"

class Serializer {

public:
    Serializer();

    bool save (Node * root, const QString & filename);

    Node * load (const QString & filename);

    void writeNode (Node * node, Node * parent, QTextStream & stream);
};

#endif // SERIALIZER_HH
