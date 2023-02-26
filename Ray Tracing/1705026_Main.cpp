#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<cmath>
#include<cstdlib>
#include<vector>

#include <windows.h>
#include <GL/glut.h>

#include "1705026_bitmap_image.hpp"
#include "1705026_Header.hpp"

#define pi (2 * acos(0.0))
#define inf 9999999
#define int_inf 2147483647

using namespace std;


class unit_vector
{
public:
    double x;
    double y;
    double z;

    unit_vector()
    {
        x = 1;
        y = 1;
        z = 1;
        // cout<<"in default"<<endl;
    }

    unit_vector(double x1, double y1, double z1)
    {
        x = x1;
        y = y1;
        z = z1;
        // cout<<"in x"<<endl;
        // cout<<x<<endl<<y<<endl<<z<<endl;
    }

    unit_vector mul_func(const double value)
    {
        unit_vector temp;
        temp.x = x * value;
        temp.y = y * value;
        temp.z = z * value;
        return temp;
    }

    unit_vector add_func(unit_vector my_vec)
    {
        unit_vector temp;
        temp.x = x + my_vec.x;
        temp.y = y + my_vec.y;
        temp.z = z + my_vec.z;
        return temp;
    }

    unit_vector sub_func(unit_vector my_vec)
    {
        unit_vector temp;
        temp.x = x - my_vec.x;
        temp.y = y - my_vec.y;
        temp.z = z - my_vec.z;
        return temp;
    }

    unit_vector cross_func(unit_vector uv)
    {
        unit_vector temp;
        temp.x = y * uv.z - z * uv.y;
        temp.y = z * uv.x - x * uv.z;
        temp.z = x * uv.y - y * uv.x;
        return temp;
    }

    void assign_func(unit_vector uv)
    {
        x = uv.x;
        y = uv.y;
        z = uv.z;
    }
};

class positions
{
public:
    double x;
    double y;
    double z;

    position()
    {
        x = 100;
        y = 100;
        z = 0;
        // cout<<x<<endl;
    }

    position(double x1, double y1, double z1)
    {
        x = x1;
        y = y1;
        z = z1;
    }

    void add_func(unit_vector my_vec)
    {
        x = x + my_vec.x;
        y = y + my_vec.y;
        z = z + my_vec.z;
    }

    unit_vector add_vec(unit_vector my_vec)
    {
        unit_vector temp;
        temp.x = x + my_vec.x;
        temp.y = y + my_vec.y;
        temp.z = z + my_vec.z;
        return temp;
    }

    void sub_func(unit_vector my_vec)
    {
        x = x - my_vec.x;
        y = y - my_vec.y;
        z = z - my_vec.z;
    }

    void mul_func(const double value)
    {
        x = x * value;
        y = y * value;
        z = z * value;
    }
};

positions pos;
unit_vector u;
unit_vector r;
unit_vector l;

double fovY;
extern Vector3D position;
int drawgrid;
int drawaxes;



extern int recursion_level;
int imgPixel_dim;
int no_of_objects;
int totalLights;
int totalSpotLights;

extern vector<Object *> objects;
extern vector<PointLight> lights;
extern vector<SpotLight> spotLights;

int image_count;

void drawAxes()
{
    if (drawaxes == 1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f(500, 0, 0);
            glVertex3f(-500, 0, 0);

            glVertex3f(0, -500, 0);
            glVertex3f(0, 500, 0);

            glVertex3f(0, 0, 500);
            glVertex3f(0, 0, -500);
        }
        glEnd();
    }
}

void drawGrid()
{
    int i;
    if (drawgrid == 1)
    {
        glColor3f(0.6, 0.6, 0.6); // grey
        glBegin(GL_LINES);
        {
            for (i = -8; i <= 8; i++)
            {

                if (i == 0)
                    continue; // SKIP the MAIN axes

                // lines parallel to Y-axis
                glVertex3f(i * 10, -90, 0);
                glVertex3f(i * 10, 90, 0);

                // lines parallel to X-axis
                glVertex3f(-90, i * 10, 0);
                glVertex3f(90, i * 10, 0);
            }
        }
        glEnd();
    }
}

int convertToint(double val)
{
    return (int)round(val);
}

void capture()
{
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
    fstream fbuffer;
    fbuffer.open("D:\\my_files\\changed_buffer.txt",ios::out);
    int windowWidth = 500;
    int windowHeight = 500;
    cout<<"("<<pos.x<<","<<pos.y<<","<<pos.z<<")"<<endl;
    cout<<"drawing image"<<endl;

    bitmap_image bitmapImage(imgPixel_dim, imgPixel_dim);

    for (int i = 0; i < imgPixel_dim; i++)
    {
        for (int j = 0; j < imgPixel_dim; j++)
        {
            bitmapImage.set_pixel(i,j,0,0,0);
        }
    }

    unit_vector temp;
    unit_vector temp2;
    unit_vector temp3;
    unit_vector temp4;
    double dist_of_plane;
    dist_of_plane = ((windowHeight*1.0)/(2.0))/(tan((fovY*pi/180.0)/(2.0)));
    unit_vector topLeft;
    temp.assign_func(l.mul_func(dist_of_plane));
    temp2.assign_func(r.mul_func(windowWidth/2.0));
    temp3.assign_func(u.mul_func(windowHeight/2.0));
    temp4.assign_func(temp.sub_func(temp2));
    temp4.assign_func(temp4.add_func(temp3));
    temp4.assign_func(pos.add_vec(temp4));
    topLeft.assign_func(temp4);


    double du,dv;
    du = (windowWidth*1.0)/imgPixel_dim;
    dv = (windowHeight*1.0)/imgPixel_dim;

    temp.assign_func(r.mul_func(du/2.0));
    temp2.assign_func(u.mul_func(dv/2.0));
    temp3.assign_func(temp.sub_func(temp2));
    topLeft.assign_func(topLeft.add_func(temp3));


    for (int i = 0; i < imgPixel_dim; i++)
    {
        for (int j = 0; j < imgPixel_dim; j++)
        {
            unit_vector curPixel;
            temp.assign_func(r.mul_func(i*du));
            temp2.assign_func(u.mul_func(j*dv));
            temp3.assign_func(temp.sub_func(temp2));
            curPixel.assign_func(topLeft.add_func(temp3));

            Vector3D position_2, curPixel_2;
            position_2.x = pos.x;
            position_2.y = pos.y;
            position_2.z = pos.z;
            curPixel_2.x = curPixel.x;
            curPixel_2.y = curPixel.y;
            curPixel_2.z = curPixel.z;
            Ray ray(position_2, curPixel_2.sub_func(position_2));

            int nearest = int_inf;
            double t;
            double tMin = inf;

            for (int i = 0; i < objects.size(); i++)
            {
                Color color;
                t = objects[i]->intersect(ray,color,0);

                if (t > 0.0 && t < tMin)
                {
                    tMin = t;
                    nearest = i;
                }
            }

            if (nearest != int_inf)
            {
                Color color;
                tMin = objects[nearest]->intersect(ray, color, 1);
                fbuffer<<convertToint(color.r*255.0)<<"    "<<convertToint(color.g*255.0)<<"    "<<convertToint(color.b*255.0)<<endl;
                bitmapImage.set_pixel(i, j, convertToint(color.r*255.0), convertToint(color.g*255.0), convertToint(color.b*255.0));
            }
        }
    }

    image_count++;
    stringstream ss;
    ss<<image_count;
    string img_cnt;
    ss>>img_cnt;


    bitmapImage.save_image("D:\\my_images\\output_" + img_cnt + ".bmp");
    cout<<"image created"<<endl;
    fbuffer.close();
}

void keyboardListener(unsigned char key, int x, int y)
{
    unit_vector temp;
    unit_vector temp2;
    switch (key)
    {
    case '0':
        capture();
        break;
    case '1':

        temp.assign_func(r.mul_func(cos((pi * 3.0) / 180.0)));
        temp2.assign_func(u.cross_func(r));
        temp2.assign_func(temp2.mul_func(sin((pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        r.assign_func(temp);

        temp.assign_func(l.mul_func(cos((pi * 3.0) / 180.0)));
        temp2.assign_func(u.cross_func(l));
        temp2.assign_func(temp2.mul_func(sin((pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        l.assign_func(temp);
        break;
    case '2':

        temp.assign_func(r.mul_func(cos((-pi * 3.0) / 180.0)));
        temp2.assign_func(u.cross_func(r));
        temp2.assign_func(temp2.mul_func(sin((-pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        r.assign_func(temp);

        temp.assign_func(l.mul_func(cos((-pi * 3.0) / 180.0)));
        temp2.assign_func(u.cross_func(l));
        temp2.assign_func(temp2.mul_func(sin((-pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        l.assign_func(temp);
        break;
    case '3':

        temp.assign_func(l.mul_func(cos((pi * 3.0) / 180.0)));
        temp2.assign_func(r.cross_func(l));
        temp2.assign_func(temp2.mul_func(sin((pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        l.assign_func(temp);

        temp.assign_func(u.mul_func(cos((pi * 3.0) / 180.0)));
        temp2.assign_func(r.cross_func(u));
        temp2.assign_func(temp2.mul_func(sin((pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        u.assign_func(temp);
        break;

    case '4':

        temp.assign_func(l.mul_func(cos((-pi * 3.0) / 180.0)));
        temp2.assign_func(r.cross_func(l));
        temp2.assign_func(temp2.mul_func(sin((-pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        l.assign_func(temp);

        temp.assign_func(u.mul_func(cos((-pi * 3.0) / 180.0)));
        temp2.assign_func(r.cross_func(u));
        temp2.assign_func(temp2.mul_func(sin((-pi * 3.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        u.assign_func(temp);
        break;
    case '5':

        temp.assign_func(u.mul_func(cos((pi * 1.0) / 180.0)));
        temp2.assign_func(l.cross_func(u));
        temp2.assign_func(temp2.mul_func(sin((pi * 1.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        u.assign_func(temp);

        temp.assign_func(r.mul_func(cos((pi * 1.0) / 180.0)));
        temp2.assign_func(l.cross_func(r));
        temp2.assign_func(temp2.mul_func(sin((pi * 1.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        r.assign_func(temp);
        break;
    case '6':

        temp.assign_func(u.mul_func(cos((-pi * 1.0) / 180.0)));
        temp2.assign_func(l.cross_func(u));
        temp2.assign_func(temp2.mul_func(sin((-pi * 1.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        u.assign_func(temp);

        temp.assign_func(r.mul_func(cos((-pi * 1.0) / 180.0)));
        temp2.assign_func(l.cross_func(r));
        temp2.assign_func(temp2.mul_func(sin((-pi * 1.0) / 180.0)));
        temp.assign_func(temp.add_func(temp2));
        r.assign_func(temp);
        break;
    default:
        break;
    }
}

void specialKeyListener(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        pos.sub_func(l.mul_func(2));
        break;
    case GLUT_KEY_UP:
        pos.add_func(l.mul_func(2));
        break;
    case GLUT_KEY_RIGHT:
        pos.add_func(r.mul_func(2));
        break;
    case GLUT_KEY_LEFT:
        pos.sub_func(r.mul_func(2));
        break;
    case GLUT_KEY_PAGE_UP:
        pos.add_func(u.mul_func(1));
        break;
    case GLUT_KEY_PAGE_DOWN:
        pos.sub_func(u.mul_func(1));
        break;
    default:
        break;
    }
}

void mouseListener(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        { // 2 times?? in ONE click? -- solution is checking DOWN or UP
            drawaxes = 1 - drawaxes;
        }
        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}

void display()
{
    // clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0); // color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    // load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    // initialize the matrix
    glLoadIdentity();
    // now give three info
    // 1. where is the camera (viewer)?
    // 2. where is the camera looking?
    // 3. Which direction is the camera's UP direction?

    // gluLookAt(100,100,100,	0,0,0,	0,0,1);
    // gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    // gluLookAt(0,0,200,	0,0,0,	0,1,0);
    gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);

    // again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    /****************************
    / Add your objects from here
    ****************************/
    // add objects

    drawAxes();
    drawGrid();

    // glColor3f(1,0,0);
    // drawSquare(10);

    // drawSS();

    // drawCircle(30,24);

    // drawCone(20,50,24);

    // drawSphere(30,24,20);

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->draw();
    }

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i].draw();
    }

    for (int i = 0; i < spotLights.size(); i++)
    {
        spotLights[i].draw();
    }

    // ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate()
{
    // angle+=0.01;
    // codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    // codes for initialization
    fovY = 80.0;
    drawgrid = 0;
    drawaxes = 1;

    pos.x = 100.0;
    pos.y = 100.0;
    pos.z = 0.0;
    u.x = 0.0;
    u.y = 0.0;
    u.z = 1.0;
    r.x = (-1 / sqrt(2));
    r.y = (1 / sqrt(2));
    r.z = 0.0;
    l.x = (-1 / sqrt(2));
    l.y = (-1 / sqrt(2));
    l.z = 0.0;

    image_count = 10;
    totalLights = 0;
    totalSpotLights = 0;

    // clear the screen
    glClearColor(0, 0, 0, 0);

    /************************
    / set-up projection here
    ************************/
    // load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    // initialize the matrix
    glLoadIdentity();

    // give PERSPECTIVE parameters
    gluPerspective(fovY, 1, 1, 1000.0);
    // field of view in the Y (vertically)
    // aspect ratio that determines the field of view in the X direction (horizontally)
    // near distance
    // far distance
}

void freeObjects()
{
    int i = 0;
    while(i < objects.size())
    {
        delete objects[i];
        i++;
    }

    objects.clear();
}

void freeLights()
{
    lights.clear();
    spotLights.clear();
}

void print_vector(Vector3D temp)
{
    cout << "printing vector" << endl;
    cout << "x is : " << temp.x << endl;
    cout << "y is : " << temp.y << endl;
    cout << "z is : " << temp.z << endl;
}

void loadData()
{
    fstream file;
    int invalid_obj = 0;
    int sphere_segments = 72;
    int sphere_stacks = 24;
    imgPixel_dim = 0;
    no_of_objects = 0;

    file.open("D:\\scene.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Cannot open file" << endl;
        exit(1);
    }

    file>>recursion_level;
    cout<<recursion_level<<endl;
    file>>imgPixel_dim;
    cout<<imgPixel_dim<<endl;
    file>>no_of_objects;
    cout<<no_of_objects<<endl;

    string obj_type;

    Object *obj = NULL;

    for (int i = 0; i < no_of_objects; i++)
    {
        file>>obj_type;
        if (obj_type == "sphere")
        {
            Vector3D center;
            double radius;

            file>>center.x;
            file>>center.y;
            file>>center.z;
            print_vector(center);
            file>>radius;
            cout<<radius<<endl;

            obj = new Sphere(center, radius, sphere_segments, sphere_stacks);
        }
        else if (obj_type == "triangle")
        {
            Vector3D vertex_A;
            Vector3D vertex_B;
            Vector3D vertex_C;

            file>>vertex_A.x;
            file>>vertex_A.y;
            file>>vertex_A.z;
            print_vector(vertex_A);

            file>>vertex_B.x;
            file>>vertex_B.y;
            file>>vertex_B.z;
            print_vector(vertex_B);

            file>>vertex_C.x;
            file>>vertex_C.y;
            file>>vertex_C.z;
            print_vector(vertex_C);

            obj = new Triangle(vertex_A, vertex_B, vertex_C);
        }
        else if (obj_type == "general")
        {
            gQuadSurfaceCo qscoefficients;
            Vector3D cube_ref_Point;
            double length;
            double width;
            double height;

            file>>qscoefficients.a;
            file>>qscoefficients.b;
            file>>qscoefficients.c;
            file>>qscoefficients.d;
            file>>qscoefficients.e;
            file>>qscoefficients.f;
            file>>qscoefficients.g;
            file>>qscoefficients.h;
            file>>qscoefficients.i;
            file>>qscoefficients.j;

            file>>cube_ref_Point.x;
            file>>cube_ref_Point.y;
            file>>cube_ref_Point.z;
            print_vector(cube_ref_Point);

            file>>length;
            file>>width;
            file>>height;

            obj = new generalQuadrics(qscoefficients, cube_ref_Point, length, width, height);
        }
        else
        {
            cout<<"undefined object shape found..."<<endl;
            cout<<obj_type<<endl;
            invalid_obj = 1;
            break;
        }

        cout<<obj_type<<endl;
        Color color;
        reflectionCo reflectionCoefficient;
        int shine;

        file>>color.r;
        file>>color.g;
        file>>color.b;
        file>>reflectionCoefficient.ambient;
        file>>reflectionCoefficient.diffuse;
        file>>reflectionCoefficient.specular;
        file>>reflectionCoefficient.recursive_co;
        file>>shine;

        obj->color.r = color.r;
        obj->color.g = color.g;
        obj->color.b = color.b;
        obj->coEfficients.ambient = reflectionCoefficient.ambient;
        obj->coEfficients.diffuse = reflectionCoefficient.diffuse;
        obj->coEfficients.specular = reflectionCoefficient.specular;
        obj->coEfficients.recursive_co = reflectionCoefficient.recursive_co;
        obj->shine = shine;

        objects.push_back(obj);
    }
    obj = NULL;

    if (invalid_obj)
    {
        freeObjects();
        file.close();
        exit(1);
    }

    file>>totalLights;

    for (int i = 0; i < totalLights; i++)
    {
        Vector3D position;
        Color color;

        file>>position.x;
        file>>position.y;
        file>>position.z;
        print_vector(position);

        file>>color.r;
        file>>color.g;
        file>>color.b;

        lights.push_back(PointLight(position,color,1.0,12,4));
    }

    file>>totalSpotLights;

    for (int i = 0; i< totalSpotLights; i++)
    {
        cout<<"spot_light"<<endl;
        Vector3D position;
        Vector3D direction;
        Color color;
        PointLight point_light;
        double cutoff_angle;

        file>>position.x;
        file>>position.y;
        file>>position.z;
        print_vector(position);

        file>>color.r;
        file>>color.g;
        file>>color.b;
        cout<<"color "<<color.r<<endl;

        file>>direction.x;
        file>>direction.y;
        file>>direction.z;
        print_vector(direction);

        file>>cutoff_angle;

        spotLights.push_back(SpotLight(PointLight(position,color,3.0,12,4),direction,cutoff_angle));
    }
    file.close();

    for (int i = 0; i<spotLights.size(); i++)
    {
        cout<<"spot_light"<<endl;
        print_vector(spotLights[i].light_direction);
        cout<<spotLights[i].cutoff_angle<<endl;
    }

    Color color_f(0.0,0.0,0.0);
    obj = new Floor(1000.0,20.0,color_f);

    obj->color.r = 1.0;
    obj->color.g = 1.0;
    obj->color.b = 1.0;
    obj->coEfficients.ambient = 0.30;
    obj->coEfficients.diffuse = 0.30;
    obj->coEfficients.specular = 0.30;
    obj->coEfficients.recursive_co = 0.30;
    obj->shine = 30;

    objects.push_back(obj);
    obj = NULL;
}

int main(int argc, char **argv)
{
    int free_lights = 1;
    int free_obj = 1;
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); // Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST); // enable Depth Testing

    glutDisplayFunc(display); // display callback function
    glutIdleFunc(animate);    // what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    free_lights = atexit(freeLights);
    free_obj = atexit(freeObjects);
    if (free_lights != 0 || free_obj != 0)
    {
        cout << "failed to clear memory for light and objects" << endl;
        exit(1);
    }

    loadData();
    glutMainLoop(); // The main loop of OpenGL

    return 0;
}
