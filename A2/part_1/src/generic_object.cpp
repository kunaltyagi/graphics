#include <generic_object.hpp>

void GenericObject::draw(void)
{
    setFlags();
    glColor4f (color.x, color.y, color.z, color.w);

    glPushMatrix();
    transformObj();
    glCallList(_drawList);
    glPopMatrix();

    Object::draw();
}

void GenericObject::transformObj(void)
{
    glRotatef(_objPose.R.w, _objPose.R.x, _objPose.R.y, _objPose.R.z);
    glTranslatef(_objPose.T.x, _objPose.T.y, _objPose.T.z);
    glScalef(scale.x, scale.y, scale.z);
}

void GenericObject::setFlags(void)
{
    glEnable(GL_LIGHTING);
    /* glEnable(GL_COLOR_MATERIAL); */
    /* glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); */
    glShadeModel (GL_SMOOTH);
}

void GenericObject::load(void)
{
    setupMaterial();
    setupObject();
}

void GenericObject::setupMaterial(void)
{
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

