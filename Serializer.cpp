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

    int id, parentId, nodeType, value;
    Node * root;
    Node * node;

    while ( ! stream.atEnd() ) {
        QString line = stream.readLine();

        // split into parts
        QStringList parts = line.split( " ", QString::SkipEmptyParts );
        if ( parts.size() != 5 ) {
            continue;
        }

        // extract all data
        id = parts[0].toInt();
        parentId = parts[1].toInt();
        nodeType = parts[2].toInt();
        value = parts[3].toInt();

        // any parent?
        if ( parentId != -1 ) {
            node = new Node( nodeData[ nodeType ], value, nodes[ parentId ] );
        }
        else {
            node = new Node( nodeData[ nodeType ], value );
            root = node;
        }

        nodes[ id ] = node;
    }

    return root;
}


void Serializer::writeNode (Node * node, Node * parent, QTextStream & stream) {
    stream << node->getId() << " " << (parent ? parent->getId() : -1 ) << " " << node->getType() << " " << node->getValue() << " " << node->getSerializationId() << endl;

    // save all children
    for ( int index = 0; index < node->childCount(); ++index ) {
        writeNode( dynamic_cast<Node *>( node->child( index ) ), node, stream );
    }
}
