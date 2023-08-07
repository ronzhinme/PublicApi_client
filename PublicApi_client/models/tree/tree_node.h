#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>

namespace DataModels
{

class TreeNode : public QObject
{
    Q_OBJECT
public:
    explicit TreeNode(QObject *parent = nullptr);

    void setRoot(TreeNode *node = nullptr);
    TreeNode* getRoot() const;

    TreeNode* getChild(int index) const;
    bool insert(TreeNode* node, int pos = -1);
    bool remove(TreeNode* node);
    void clear();
    QList<TreeNode*> getChildren() const;

    int pos(bool fromRoot) const;
    uint getId() const;
private:
    TreeNode *root_;
    QList<TreeNode*> children_;
    uint id_;
};

}

#endif // TREENODE_H
