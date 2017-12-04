import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import Examples 1.0

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, -40.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    OrbitCameraController {
        camera: camera
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(0, 0.5, 1, 1)
                camera: camera
            }
        },
        // Event Source will be set by the Qt3DQuickWindow
        InputSettings { }
    ]

    PerVertexColorMaterial {
        id: material
    }

    CustomMesh {
        id: tetrahedron
    }

    Transform {
        id: transform
        scale: 8.0
    }

    Entity {
        id: torusEntity
        components: [ tetrahedron, material, transform ]
    }
}
