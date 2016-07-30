#ifndef TREE_HH
#define TREE_HH

#include <QTreeWidget>

class Tree : public QTreeWidget {

public:

    Tree( QWidget * parent=0);

private:

    virtual void dropEvent (QDropEvent * event);
};

#endif // TREE_HH
