
#include <QDropEvent>
#include <QDebug>

#include "Tree.hpp"
#include "NodeTypes.hpp"

Tree::Tree(QWidget * parent) : QTreeWidget(parent) {

}


void Tree::dropEvent(QDropEvent * event) {
    Node * node = dynamic_cast<Node *>( itemAt(event->pos()) );
    if ( ! node ) {
        // must be dropped on a node
        return;
    }

    QTreeWidget::dropEvent(event);
}
