#include <generic_object.hpp>

void GenericObject::draw(void)
{
    setFlags();
    /* std::cout << "Color: " << color << '\n'; */
    glColor4f (color.x, color.y, color.z, color.w);

    glPushMatrix();
    transformObj();
#if 0
    glCallList(_drawList);
#else
    this->drawObject();
#endif
    glPopMatrix();

    Object::draw();
}

void GenericObject::input(int key)
{
    for (auto& joint : _jointVec)
    {
        joint->input(key);
    }
}


void GenericObject::transformObj(void)
{
    /* std::cout << "Origin: " << _origin << */
    /*              " Pose: " << _objPose.T << _objPose.R << '\n'; */
    glRotatef(_objPose.R.w, _objPose.R.x, _objPose.R.y, _objPose.R.z);
    glTranslatef(-_origin.x, -_origin.y, -_origin.z);
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
    for (auto& joint : _jointVec)
    {
        joint->load();
    }
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

