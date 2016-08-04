#include <QFile>
#include <QMessageBox>
#include <QMap>
#include <QDebug>

#include "Serializer.hpp"

Serializer::Serializer() {

}

bool Serializer::save (Node * root, const QString & filename) {
    QFile file( filename );
    if ( ! file.open( QIODevice::WriteOnly |QIODevice::Truncate ) ) {
        // failed
        QMessageBox::warning( 0, "Save Failed", "Failed to save the map: " + file.errorString(), QMessageBox::Ok );
        return false;
    }


    // save the real map to a stream
    QTextStream stream( &file );

    // save all nodes
    writeNode( root, nullptr, stream );

    return true;
}


Node * Serializer::load (const QString & filename) {
    QFile file( filename );
    if ( ! file.open( QIODevice::ReadOnly ) ) {
        QMessageBox::warning( 0, "Open Failed", "Failed to open the map: " + file.errorString(), QMessageBox::Ok );
        return nullptr;
    }

    // a map of all nodes so that new nodes can find their parent. initially the root
    QMap<int, Node *> nodes;

    QTextStream stream( &file );

    int id, parentId, nodeType;
    QString value, comment;
    Node * root;
    Node * node;

    while ( ! stream.atEnd() ) {
        QString line = stream.readLine();

        // split into parts
        QStringList parts = line.split( " ", QString::SkipEmptyParts );
        QString key = parts.takeFirst();

        // what did we get?
        if ( key == "id" ) {
            // new node starts, clear all data that is not always present
            value = "";
            comment = "";

            id = parts.first().toInt();
        }

        else if ( key == "parent" ) {
            parentId = parts.first().toInt();
        }

        else if ( key == "type" ) {
            nodeType = parts.first().toInt();
        }

        else if ( key== "class" ) {
            // skip
        }

        else if ( key == "value" ) {
            value = parts.join( " " );
        }

        else if ( key == "comment" ) {
            comment = parts.join( " " );

            // now the node is complete
            if ( parentId != -1 ) {
                node = new Node( nodeData[ nodeType ], value, nodes[ parentId ] );
            }
            else {
                node = new Node( nodeData[ nodeType ], value );
                root = node;
            }

            node->setComment( comment );
            node->setup();

            nodes[ id ] = node;
        }

        else {
            qDebug() << "unknown key: " << key;
        }
    }

    return root;
}


void Serializer::writeNode (Node * node, Node * parent, QTextStream & stream) {
    stream << "id " << node->getId() << endl
           << "parent " << (parent ? parent->getId() : -1 ) << endl
           << "type " << node->getType() << endl
           << "class " << node->getSerializationId() << endl
           << "value " << node->getValue() << endl
           << "comment " << node->getComment() << endl;

    // save all children
    for ( int index = 0; index < node->childCount(); ++index ) {
        writeNode( dynamic_cast<Node *>( node->child( index ) ), node, stream );
    }
}
