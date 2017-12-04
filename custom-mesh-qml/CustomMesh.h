#ifndef CUSTOMMESH_H
#define CUSTOMMESH_H

#include <Qt3DRender/QGeometryRenderer>

class CustomMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT

public:
    explicit CustomMesh(Qt3DCore::QNode *parent = nullptr);
    ~CustomMesh();
};

#endif // CUSTOMMESH_H
