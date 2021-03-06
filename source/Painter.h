
#pragma once

#include <QMatrix4x4>
#include <QMap>
#include <QVector3D>

#include "AbstractPainter.h"

class QOpenGLShader;
class QOpenGLShaderProgram;

class Camera;
class ScreenAlignedQuad;
class PatchedTerrain;


class Painter : public AbstractPainter
{
public:
    Painter();
    virtual ~Painter();

    virtual bool initialize();

    virtual void paint(float timef);
    virtual void resize(
        int width
    ,   int height);

    virtual void update();
    virtual void update(const QList<QOpenGLShaderProgram *> & programs);

    void keyPressEvent(QKeyEvent * event);

protected:

    void bindEnvMaps(GLenum target);
    void unbindEnvMaps(GLenum target);

    void paint_4_1(float timef);

protected:
    QOpenGLShaderProgram * createBasicShaderProgram(
        const QString & vertexShaderFileName
    ,   const QString & fragmentShaderFileName);

    QOpenGLShaderProgram * createBasicShaderProgram(
        const QString & vertexShaderFileName
    ,   const QString & geometryShaderFileName
    ,   const QString & fragmentShaderFileName);
    void patchify();
    void patchify(
        float extend
    ,   float x
    ,   float z
    ,   int level);
    void patchify(
        float extend
    ,   QPointF center
    ,   int level);
    void drawP(
        float extend
    ,   float x
    ,   float z
    ,   int level);
    float height(
        const float x
    ,   const float z) const;
    int levelFromDistance(float distance);
    bool cull(
        const QVector4D & v0);

    // ...

protected:
    Camera * m_camera;

    ScreenAlignedQuad * m_quad;

    QList<QMatrix4x4> m_transforms;

    QMap<int, QOpenGLShaderProgram *> m_programs;
    QList<QOpenGLShader *> m_shaders;

    PatchedTerrain * m_terrain;

    std::vector<unsigned short> m_heights;

    float m_yScale;
    float m_yOffset;
    int m_maximumDetail;

    GLuint m_height;
    GLuint m_normals;
    GLuint m_diffuse;
    GLuint m_detail;
    GLuint m_detailn;

    bool m_drawLineStrips;
    bool m_debug;

    float m_precission;
    int m_level;
    QVector3D m_cachedEye;
    QVector3D m_cameraPos;
    QVector4D m_clearColor;
};
