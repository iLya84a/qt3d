#include "CustomMesh.h"

#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>

#include <QVector3D>
#include <QDebug>

// Custom Geometry (Tetrahedron)
class CustomGeometry : public Qt3DRender::QGeometry
{
    Q_OBJECT

public:
    CustomGeometry(Qt3DCore::QNode *parent = Q_NULLPTR)
        : Qt3DRender::QGeometry(parent)
        , m_vertexDataBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, this))
        , m_indexDataBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, this))
    {
        // vec3 for position
        // vec3 for colors
        // vec3 for normals

        /*          2
                   /|\
                  / | \
                 / /3\ \
                 0/___\ 1
        */

        // 4 distinct vertices
        QByteArray vertexBufferData;
        vertexBufferData.resize(4 * (3 + 3 + 3) * sizeof(float));

        // Vertices
        QVector3D v0(-1.0f, 0.0f, -1.0f);
        QVector3D v1(1.0f, 0.0f, -1.0f);
        QVector3D v2(0.0f, 1.0f, 0.0f);
        QVector3D v3(0.0f, 0.0f, 1.0f);

        // Faces Normals
        QVector3D n023 = QVector3D::normal(v0, v2, v3);
        QVector3D n012 = QVector3D::normal(v0, v1, v2);
        QVector3D n310 = QVector3D::normal(v3, v1, v0);
        QVector3D n132 = QVector3D::normal(v1, v3, v2);

        // Vector Normals
        QVector3D n0 = QVector3D(n023 + n012 + n310).normalized();
        QVector3D n1 = QVector3D(n132 + n012 + n310).normalized();
        QVector3D n2 = QVector3D(n132 + n012 + n023).normalized();
        QVector3D n3 = QVector3D(n132 + n310 + n023).normalized();

        // Colors
        QVector3D red(1.0f, 0.0f, 0.0f);
        QVector3D green(0.0f, 1.0f, 0.0f);
        QVector3D blue(0.0f, 0.0f, 1.0f);
        QVector3D white(1.0f, 1.0f, 1.0f);

        QVector<QVector3D> vertices = QVector<QVector3D>()
                << v0 << n0 << red
                << v1 << n1 << blue
                << v2 << n2 << green
                << v3 << n3 << white;

        float *rawVertexArray = reinterpret_cast<float *>(vertexBufferData.data());
        int idx = 0;

        Q_FOREACH (const QVector3D &v, vertices) {
            rawVertexArray[idx++] = v.x();
            rawVertexArray[idx++] = v.y();
            rawVertexArray[idx++] = v.z();
        }

        // Indices (12)
        QByteArray indexBufferData;
        indexBufferData.resize(4 * 3 * sizeof(ushort));
        ushort *rawIndexArray = reinterpret_cast<ushort *>(indexBufferData.data());

        // Front
        rawIndexArray[0] = 0;
        rawIndexArray[1] = 1;
        rawIndexArray[2] = 2;
        // Bottom
        rawIndexArray[3] = 3;
        rawIndexArray[4] = 1;
        rawIndexArray[5] = 0;
        // Left
        rawIndexArray[6] = 0;
        rawIndexArray[7] = 2;
        rawIndexArray[8] = 3;
        // Right
        rawIndexArray[9] = 1;
        rawIndexArray[10] = 3;
        rawIndexArray[11] = 2;

        m_vertexDataBuffer->setData(vertexBufferData);
        m_indexDataBuffer->setData(indexBufferData);

        // Attributes
        Qt3DRender::QAttribute *positionAttribute = new Qt3DRender::QAttribute();
        positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        positionAttribute->setBuffer(m_vertexDataBuffer);
        positionAttribute->setDataType(Qt3DRender::QAttribute::Float);
        positionAttribute->setDataSize(3);
        positionAttribute->setByteOffset(0);
        positionAttribute->setByteStride(9 * sizeof(float));
        positionAttribute->setCount(4);
        positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

        Qt3DRender::QAttribute *normalAttribute = new Qt3DRender::QAttribute();
        normalAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        normalAttribute->setBuffer(m_vertexDataBuffer);
        normalAttribute->setDataType(Qt3DRender::QAttribute::Float);
        normalAttribute->setDataSize(3);
        normalAttribute->setByteOffset(3 * sizeof(float));
        normalAttribute->setByteStride(9 * sizeof(float));
        normalAttribute->setCount(4);
        normalAttribute->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());

        Qt3DRender::QAttribute *colorAttribute = new Qt3DRender::QAttribute();
        colorAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        colorAttribute->setBuffer(m_vertexDataBuffer);
        colorAttribute->setDataType(Qt3DRender::QAttribute::Float);
        colorAttribute->setDataSize(3);
        colorAttribute->setByteOffset(6 * sizeof(float));
        colorAttribute->setByteStride(9 * sizeof(float));
        colorAttribute->setCount(4);
        colorAttribute->setName(Qt3DRender::QAttribute::defaultColorAttributeName());

        Qt3DRender::QAttribute *indexAttribute = new Qt3DRender::QAttribute();
        indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
        indexAttribute->setBuffer(m_indexDataBuffer);
        indexAttribute->setDataType(Qt3DRender::QAttribute::UnsignedShort);
        indexAttribute->setDataSize(1);
        indexAttribute->setByteOffset(0);
        indexAttribute->setByteStride(0);
        indexAttribute->setCount(12);

        addAttribute(positionAttribute);
        addAttribute(normalAttribute);
        addAttribute(colorAttribute);
        addAttribute(indexAttribute);
    }

private:
    Qt3DRender::QBuffer *m_vertexDataBuffer;
    Qt3DRender::QBuffer *m_indexDataBuffer;
};

CustomMesh::CustomMesh(Qt3DCore::QNode *parent)
    : Qt3DRender::QGeometryRenderer(parent)
{
    setInstanceCount(1);
    setFirstVertex(0);
    setFirstInstance(0);
    setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
    setGeometry(new CustomGeometry(this));
    // 4 faces of 3 points
    setVertexCount(12);
}

CustomMesh::~CustomMesh()
{
}

#include "CustomMesh.moc"
