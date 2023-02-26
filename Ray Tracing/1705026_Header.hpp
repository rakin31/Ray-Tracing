#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
#include<cmath>

#define pi (2 * acos(0.0))
#define inf 9999999
#define int_inf 2147483647

using namespace std;


class Vector3D
{
public:

    double x;
    double y;
    double z;

    Vector3D()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector3D(double x1, double y1, double z1)
    {
        x = x1;
        y = y1;
        z = z1;
    }

    double magnitude()
    {
        double val;
        val = sqrt(x*x + y*y + z*z);
        return val;
    }

    void normalize()
    {
        double val;
        val = sqrt(x*x + y*y + z*z);
        x = x/val;
        y = y/val;
        z = z/val;
    }

    double vec_distance(Vector3D my_vec)
    {
        double x_diff, y_diif, z_diff;
        x_diff = x - my_vec.x;
        y_diif = y - my_vec.y;
        z_diff = z - my_vec.z;
        double val;
        val = sqrt(x_diff * x_diff + y_diif * y_diif + z_diff * z_diff);
        return val;
    }

    Vector3D add_func(Vector3D my_vec)
    {
        Vector3D temp;
        temp.x = x + my_vec.x;
        temp.y = y + my_vec.y;
        temp.z = z + my_vec.z;
        return temp;
    }

    Vector3D sub_func(Vector3D my_vec)
    {
        Vector3D temp;
        temp.x = x - my_vec.x;
        temp.y = y - my_vec.y;
        temp.z = z - my_vec.z;
        return temp;
    }

    Vector3D mul_func(const double value)
    {
        Vector3D temp;
        temp.x = x * value;
        temp.y = y * value;
        temp.z = z * value;
        return temp;
    }

    double dot_func(Vector3D my_vec)
    {
        double dot_val = 0.0;
        dot_val = x * my_vec.x + y * my_vec.y + z * my_vec.z;
        return dot_val;
    }

    Vector3D cross_func(Vector3D uv)
    {
        Vector3D temp;
        temp.x = y * uv.z - z * uv.y;
        temp.y = z * uv.x - x * uv.z;
        temp.z = x * uv.y - y * uv.x;
        return temp;
    }

    double getAngle(Vector3D vec1, Vector3D vec2)
    {
        double dot_val;
        dot_val = vec1.dot_func(vec2);
        double cos_theta = (dot_val*1.0)/(vec1.magnitude() * vec2.magnitude());
        return acos(cos_theta);
    }

    void assign_func(Vector3D uv)
    {
        x = uv.x;
        y = uv.y;
        z = uv.z;
    }

    ~Vector3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};



class Color
{
public:

    double r;
    double g;
    double b;

    Color()
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

    Color(double red, double green, double blue)
    {
        r = red;
        g = green;
        b = blue;
    }

    ~Color()
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }
};

class Ray
{

public:

    Vector3D ray_start;
    Vector3D ray_direction;

    Ray()
    {
        ray_start.x = 0.0;
        ray_start.y = 0.0;
        ray_start.z = 0.0;
        ray_direction.x = 0.0;
        ray_direction.y = 0.0;
        ray_direction.z = 0.0;
    }

    Ray(Vector3D ray_start1, Vector3D ray_direction1)
    {
        ray_start.assign_func(ray_start1);
        ray_direction.assign_func(ray_direction1);
        ray_direction.normalize();
    }

    ~Ray()
    {
        ray_start.x = 0.0;
        ray_start.y = 0.0;
        ray_start.z = 0.0;
        ray_direction.x = 0.0;
        ray_direction.y = 0.0;
        ray_direction.z = 0.0;
    }
};


class PointLight
{
public:

    Vector3D light_pos;
    double radius;
    Color color;
    int segments;
    int stacks;

    PointLight()
    {
        light_pos.x = 0.0;
        light_pos.y = 0.0;
        light_pos.z = 0.0;
        radius = 0.0;
        segments = 0;
        stacks = 0;
    }

    PointLight(Vector3D pos, Color color1, double rad, int seg, int stks)
    {
        light_pos.assign_func(pos);
        radius = rad;
        color.r = color1.r;
        color.g = color1.g;
        color.b = color1.b;
        segments = seg;
        stacks = stks;
    }

    void draw()
    {
        Vector3D points[stacks+1][segments+1];
        int i,j;
        double h,r;

        //generate points
        for(i=0;i<=stacks;i++)
        {
            h=radius*sin(((double)i/(double)stacks)*(pi/2));
            r=radius*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=segments;j++)
            {
                points[i][j].x=r*cos(((double)j/(double)segments)*2*pi);
                points[i][j].y=r*sin(((double)j/(double)segments)*2*pi);
                points[i][j].z=h;
            }
        }


        glColor3f(color.r, color.g, color.b);
        //draw quads using generated points
        for(i=0;i<stacks;i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<segments;j++)
            {
                glBegin(GL_QUADS);{
                    //upper hemisphere
                    glVertex3f(light_pos.add_func(points[i][j]).x, light_pos.add_func(points[i][j]).y, light_pos.add_func(points[i][j]).z);
                    glVertex3f(light_pos.add_func(points[i][j+1]).x, light_pos.add_func(points[i][j+1]).y, light_pos.add_func(points[i][j+1]).z);
                    glVertex3f(light_pos.add_func(points[i+1][j+1]).x, light_pos.add_func(points[i+1][j+1]).y, light_pos.add_func(points[i+1][j+1]).z);
                    glVertex3f(light_pos.add_func(points[i+1][j]).x, light_pos.add_func(points[i+1][j]).y, light_pos.add_func(points[i+1][j]).z);
                    //lower hemisphere
                    glVertex3f(light_pos.add_func(points[i][j]).x, light_pos.add_func(points[i][j]).y, light_pos.sub_func(points[i][j]).z);
                    glVertex3f(light_pos.add_func(points[i][j+1]).x, light_pos.add_func(points[i][j+1]).y, light_pos.sub_func(points[i][j+1]).z);
                    glVertex3f(light_pos.add_func(points[i+1][j+1]).x, light_pos.add_func(points[i+1][j+1]).y, light_pos.sub_func(points[i+1][j+1]).z);
                    glVertex3f(light_pos.add_func(points[i+1][j]).x, light_pos.add_func(points[i+1][j]).y, light_pos.sub_func(points[i+1][j]).z);
                }glEnd();
            }
        }
    }

    ~PointLight()
    {
        light_pos.x = 0.0;
        light_pos.y = 0.0;
        light_pos.z = 0.0;
        radius = 0.0;
        segments = 0;
        stacks = 0;
    }
};


class SpotLight
{
public:

    PointLight point_light;
    Vector3D light_direction;
    double cutoff_angle;

    SpotLight()
    {
        cutoff_angle = 0.0;
    }

    SpotLight(PointLight point_light1, Vector3D light_direction1, double cutoff_angle1)
    {
        point_light = point_light1;
        light_direction = light_direction1;
        cutoff_angle = cutoff_angle1;
    }

    void draw()
    {
        int stacks = point_light.stacks;
        int segments = point_light.segments;
        double radius = point_light.radius;

        Vector3D points[stacks+1][segments+1];
        int i,j;
        double h,r;

        //generate points
        for(i=0;i<=stacks;i++)
        {
            h=radius*sin(((double)i/(double)stacks)*(pi/2));
            r=radius*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=segments;j++)
            {
                points[i][j].x=r*cos(((double)j/(double)segments)*2*pi);
                points[i][j].y=r*sin(((double)j/(double)segments)*2*pi);
                points[i][j].z=h;
            }
        }


        glColor3f(point_light.color.r, point_light.color.g, point_light.color.b);
        //draw quads using generated points
        for(i=0;i<stacks;i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<segments;j++)
            {
                glBegin(GL_QUADS);{
                    //upper hemisphere
                    glVertex3f(point_light.light_pos.add_func(points[i][j]).x, point_light.light_pos.add_func(points[i][j]).y, point_light.light_pos.add_func(points[i][j]).z);
                    glVertex3f(point_light.light_pos.add_func(points[i][j+1]).x, point_light.light_pos.add_func(points[i][j+1]).y, point_light.light_pos.add_func(points[i][j+1]).z);
                    glVertex3f(point_light.light_pos.add_func(points[i+1][j+1]).x, point_light.light_pos.add_func(points[i+1][j+1]).y, point_light.light_pos.add_func(points[i+1][j+1]).z);
                    glVertex3f(point_light.light_pos.add_func(points[i+1][j]).x, point_light.light_pos.add_func(points[i+1][j]).y, point_light.light_pos.add_func(points[i+1][j]).z);
                    //lower hemisphere
                    glVertex3f(point_light.light_pos.add_func(points[i][j]).x, point_light.light_pos.add_func(points[i][j]).y, point_light.light_pos.sub_func(points[i][j]).z);
                    glVertex3f(point_light.light_pos.add_func(points[i][j+1]).x, point_light.light_pos.add_func(points[i][j+1]).y, point_light.light_pos.sub_func(points[i][j+1]).z);
                    glVertex3f(point_light.light_pos.add_func(points[i+1][j+1]).x, point_light.light_pos.add_func(points[i+1][j+1]).y, point_light.light_pos.sub_func(points[i+1][j+1]).z);
                    glVertex3f(point_light.light_pos.add_func(points[i+1][j]).x, point_light.light_pos.add_func(points[i+1][j]).y, point_light.light_pos.sub_func(points[i+1][j]).z);
                }glEnd();
            }
        }
    }

    ~SpotLight()
    {
        cutoff_angle = 0.0;
    }
};

class reflectionCo
{
public:

    double ambient;
    double diffuse;
    double specular;
    double recursive_co;

    reflectionCo()
    {
        ambient = 0.0;
        diffuse = 0.0;
        specular = 0.0;
        recursive_co = 0.0;
    }

    reflectionCo(double ambient1, double diffuse1, double specular1, double recursive_co1)
    {
        ambient = ambient1;
        diffuse = diffuse1;
        specular = specular1;
        recursive_co = recursive_co1;
    }

    ~reflectionCo()
    {
        ambient = 0.0;
        diffuse = 0.0;
        specular = 0.0;
        recursive_co = 0.0;
    }
};

class Object
{
public:

    Color color;
    reflectionCo coEfficients;
    int shine;

    Object()
    {
        color.r = 0.0;
        color.g = 0.0;
        color.b = 0.0;
        coEfficients.ambient = 0.0;
        coEfficients.diffuse = 0.0;
        coEfficients.specular = 0.0;
        coEfficients.recursive_co = 0.0;
        shine = 0;
    }

    void ambientComputation(Color &color, Color intersectionPointColor)
    {
        color.r = intersectionPointColor.r * coEfficients.ambient;
        color.g = intersectionPointColor.g * coEfficients.ambient;
        color.b = intersectionPointColor.b * coEfficients.ambient;
    }

    void reflectionComputation(Ray ray, Ray incidentRay, Vector3D normal, Color &color, Vector3D intersectionPoint, Color intersectionPointColor, PointLight light)
    {
        Vector3D temp;
        Vector3D temp2;
        double lambertValue;
        temp.assign_func(incidentRay.ray_direction.mul_func(-1.0));
        lambertValue = temp.dot_func(normal);

        double dot_val = incidentRay.ray_direction.dot_func(normal);
        dot_val = dot_val * 2.0;
        //temp.assign_func(incidentRay.ray_direction.sub_func(normal));
        temp.assign_func(normal.mul_func(dot_val));
        temp2.assign_func(incidentRay.ray_direction.sub_func(temp));

        Ray reflectedRay(intersectionPoint, temp2);
        double phongValue;
        temp.assign_func(ray.ray_direction.mul_func(-1.0));
        phongValue = temp.dot_func(reflectedRay.ray_direction);

        double max_valL = max(lambertValue,0.0);
        double max_valP = max(phongValue,0.0);

        color.r = color.r + light.color.r * intersectionPointColor.r * coEfficients.diffuse * max_valL;
        color.g = color.g + light.color.g * intersectionPointColor.g * coEfficients.diffuse * max_valL;
        color.b = color.b + light.color.b * intersectionPointColor.b * coEfficients.diffuse * max_valL;

        color.r = color.r + light.color.r * intersectionPointColor.r * coEfficients.specular * pow(max_valP, shine);
        color.g = color.g + light.color.g * intersectionPointColor.g * coEfficients.specular * pow(max_valP, shine);
        color.b = color.b + light.color.b * intersectionPointColor.b * coEfficients.specular * pow(max_valP, shine);
    }

    void recursiveRComputation(Color &color, Color reflectedColor)
    {
        color.r = color.r + reflectedColor.r * coEfficients.recursive_co;
        color.g = color.g + reflectedColor.g * coEfficients.recursive_co;
        color.b = color.b + reflectedColor.b * coEfficients.recursive_co;
    }

    virtual void draw() = 0;
    virtual double intersect(Ray, Color &, int) = 0;

    ~Object()
    {
        color.r = 0.0;
        color.g = 0.0;
        color.b = 0.0;
        coEfficients.ambient = 0.0;
        coEfficients.diffuse = 0.0;
        coEfficients.specular = 0.0;
        coEfficients.recursive_co = 0.0;
        shine = 0;
    }
};


vector<Object *> objects;
vector<PointLight> lights;
vector<SpotLight> spotLights;
Vector3D position;
int recursion_level = 0;


class Sphere : public Object
{
public:

    Vector3D center;
    double radius;
    int segments;
    int stacks;

    Sphere()
    {
        radius = 0.0;
        segments = 0;
        stacks = 0;
    }

    Sphere(Vector3D center1, double radius1, int segments1, int stacks1)
    {
        center = center1;
        radius = radius1;
        segments = segments1;
        stacks = stacks1;
    }

    void draw()
    {
        Vector3D points[stacks+1][segments+1];
        int i,j;
        double h,r;

        //generate points
        for(i=0;i<=stacks;i++)
        {
            h=radius*sin(((double)i/(double)stacks)*(pi/2));
            r=radius*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=segments;j++)
            {
                points[i][j].x=r*cos(((double)j/(double)segments)*2*pi);
                points[i][j].y=r*sin(((double)j/(double)segments)*2*pi);
                points[i][j].z=h;
            }
        }


        glColor3f(color.r, color.g, color.b);
        //draw quads using generated points
        for(i=0;i<stacks;i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<segments;j++)
            {
                glBegin(GL_QUADS);{
                    //upper hemisphere
                    glVertex3f(center.add_func(points[i][j]).x, center.add_func(points[i][j]).y, center.add_func(points[i][j]).z);
                    glVertex3f(center.add_func(points[i][j+1]).x, center.add_func(points[i][j+1]).y, center.add_func(points[i][j+1]).z);
                    glVertex3f(center.add_func(points[i+1][j+1]).x, center.add_func(points[i+1][j+1]).y, center.add_func(points[i+1][j+1]).z);
                    glVertex3f(center.add_func(points[i+1][j]).x, center.add_func(points[i+1][j]).y, center.add_func(points[i+1][j]).z);
                    //lower hemisphere
                    glVertex3f(center.add_func(points[i][j]).x, center.add_func(points[i][j]).y, center.sub_func(points[i][j]).z);
                    glVertex3f(center.add_func(points[i][j+1]).x, center.add_func(points[i][j+1]).y, center.sub_func(points[i][j+1]).z);
                    glVertex3f(center.add_func(points[i+1][j+1]).x, center.add_func(points[i+1][j+1]).y, center.sub_func(points[i+1][j+1]).z);
                    glVertex3f(center.add_func(points[i+1][j]).x, center.add_func(points[i+1][j]).y, center.sub_func(points[i+1][j]).z);
                }glEnd();
            }
        }
    }

    double intersect(Ray ray, Color &color, int level)
    {
        double a,b,c;
        double or_dir_dot_val;
        double dir_cen_dot_val;
        double origin_square;
        double center_square;
        double or_cen_dot_val;
        double tMin;

        a = ray.ray_direction.dot_func(ray.ray_direction);
        or_dir_dot_val = ray.ray_start.dot_func(ray.ray_direction);
        dir_cen_dot_val = ray.ray_direction.dot_func(center);
        b = (or_dir_dot_val - dir_cen_dot_val)*2.0;
        origin_square = ray.ray_start.dot_func(ray.ray_start);
        center_square = center.dot_func(center);
        or_cen_dot_val = ray.ray_start.dot_func(center);
        c = origin_square + center_square - or_cen_dot_val*2.0 - radius*radius;

        double discriminant;
        discriminant = b*b - 4.0*a*c;

        if (discriminant < 0.0)
        {
            tMin = inf;
        }
        else if (discriminant > 0.0)
        {
            double tMax;
            tMax = (-b + sqrt(discriminant))/(2.0 * a);
            tMin = (-b - sqrt(discriminant))/(2.0 * a);
            if (tMin < 0)
                tMin = tMax;
        }
        else
        {
            tMin = -b/(2.0 * a);
        }

        if (level == 0)
        {
            return tMin;
        }

        Vector3D intersectionPoint;
        Vector3D temp;
        temp.assign_func(ray.ray_direction.mul_func(tMin));
        intersectionPoint.assign_func(ray.ray_start.add_func(temp));
        Color intersectionPointColor = Object::color;


        Vector3D normal;
        normal.assign_func(intersectionPoint.sub_func(center));
        normal.normalize();
        if (position.vec_distance(center) <= radius)
            normal.assign_func(normal.mul_func(-1.0));



        ambientComputation(color, intersectionPointColor);


        for (int i = 0; i < lights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(lights[i].light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(lights[i].light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));


            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,lights[i]);
        }

        for (int i = 0; i < spotLights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(spotLights[i].point_light.light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(spotLights[i].point_light.light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            Vector3D v;
            temp.x = spotLights[i].light_direction.x;
            temp.y = spotLights[i].light_direction.y;
            temp.z = spotLights[i].light_direction.z;
            temp.normalize();
            //spotLights[i].light_direction.normalize();
            double angle = v.getAngle(incidentRay.ray_direction,temp);

            if (angle > (spotLights[i].cutoff_angle * ((pi*1.0)/180.0)))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,spotLights[i].point_light);
        }


        if (level >= recursion_level)
            return tMin;


        Vector3D reflectionDirection;
        double dir_normal_dot_val;
        dir_normal_dot_val = ray.ray_direction.dot_func(normal);
        dir_normal_dot_val = dir_normal_dot_val*2.0;
        temp.assign_func(normal.mul_func(dir_normal_dot_val));
        reflectionDirection.assign_func(ray.ray_direction.sub_func(temp));
        reflectionDirection.normalize();
        Ray reflectedRay;
        reflectedRay.ray_start.assign_func(intersectionPoint.add_func(reflectionDirection));
        reflectedRay.ray_direction.assign_func(reflectionDirection);
        reflectedRay.ray_direction.normalize();


        int nearest = int_inf;
        double t;
        double tMinimum = inf;

        int my_object = 0;
        while(my_object < objects.size())
        {
            Color dcolor;
            t = objects[my_object]->intersect(reflectedRay,dcolor,0);

            if (t > 0.0)
            {
                if ( t < tMinimum)
                {
                    tMinimum = t;
                    nearest = my_object;
                }
            }
            my_object++;
        }


        Color reflectedColor;

        if (nearest != int_inf)
            tMinimum = objects[nearest]->intersect(reflectedRay,reflectedColor,level + 1);


        recursiveRComputation(color,reflectedColor);

        if (color.r > 1.0)
            color.r = 1.0;
        else if (color.r < 0.0)
            color.r = 0.0;

        if (color.g > 1.0)
            color.g = 1.0;
        else if (color.g < 0.0)
            color.g = 0.0;

        if (color.b > 1.0)
            color.b = 1.0;
        else if (color.b < 0.0)
            color.b = 0.0;

        return tMin;
    }

    ~Sphere()
    {
        radius = 0.0;
        segments = 0;
        stacks = 0;
    }
};



class Triangle : public Object
{
public:

    Vector3D a;
    Vector3D b;
    Vector3D c;

    Triangle()
    {
        a.x = 0;
        a.y = 0;
        a.z = 0;
        b.x = 0;
        b.y = 0;
        b.z = 0;
        c.x = 0;
        c.y = 0;
        c.z = 0;
    }

    Triangle(Vector3D a1, Vector3D b1, Vector3D c1)
    {
        a = a1;
        b = b1;
        c = c1;
    }

    void draw()
    {
        glColor3f(color.r,color.g,color.b);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(a.x, a.y, a.z);
            glVertex3f(b.x, b.y, b.z);
            glVertex3f(c.x, c.y, c.z);
        }
        glEnd();
    }

    double intersect(Ray ray, Color &color, int level)
    {
        Vector3D temp;
        Vector3D temp2;
        double dt_base;
        double dt_beta;
        double dt_gamma;
        double dt_t;
        double tMin;

        dt_base = (a.x - b.x) * ((a.y - c.y) * ray.ray_direction.z - (a.z - c.z) * ray.ray_direction.y);
        dt_base = dt_base + (a.x - c.x) * ((a.z - b.z) * ray.ray_direction.y - (a.y - b.y) * ray.ray_direction.z);
        dt_base = dt_base + ray.ray_direction.x * ((a.y - b.y) * (a.z - c.z) - (a.z - b.z) * (a.y - c.y));

        dt_beta = (a.x - ray.ray_start.x) * ((a.y - c.y) * ray.ray_direction.z - (a.z - c.z) * ray.ray_direction.y);
        dt_beta = dt_beta + (a.x - c.x) * ((a.z - ray.ray_start.z) * ray.ray_direction.y - (a.y - ray.ray_start.y) * ray.ray_direction.z);
        dt_beta = dt_beta + ray.ray_direction.x * ((a.y - ray.ray_start.y) * (a.z - c.z) - (a.z - ray.ray_start.z) * (a.y - c.y));

        dt_gamma = (a.x - b.x) * ((a.y - ray.ray_start.y) * ray.ray_direction.z - (a.z - ray.ray_start.z) * ray.ray_direction.y);
        dt_gamma = dt_gamma + (a.x - ray.ray_start.x) * ((a.z - b.z) * ray.ray_direction.y - (a.y - b.y) * ray.ray_direction.z);
        dt_gamma = dt_gamma + ray.ray_direction.x * ((a.y - b.y) * (a.z - ray.ray_start.z) - (a.z - b.z) * (a.y - ray.ray_start.y));

        dt_t = (a.x - b.x) * ((a.y - c.y) * (a.z - ray.ray_start.z) - (a.z - c.z) * (a.y - ray.ray_start.y));
        dt_t = dt_t + (a.x - c.x) * ((a.z - b.z) * (a.y - ray.ray_start.y) - (a.y - b.y) * (a.z - ray.ray_start.z));
        dt_t = dt_t + (a.x - ray.ray_start.x) * ((a.y - b.y) * (a.z - c.z) - (a.z - b.z) * (a.y - c.y));

        if (dt_base == 0.0)
        {
            tMin = inf;
        }
        else
        {
            bool cond_1 = ((dt_beta/dt_base) > 0.0);
            bool cond_2 = ((dt_gamma/dt_base) > 0.0);
            bool cond_3 = ((dt_beta/dt_base) + (dt_gamma/dt_base) < 1.0);
            if (cond_1 && cond_2 && cond_3)
            {
                tMin = dt_t / dt_base;
            }
            else
            {

                tMin = inf;
            }
        }

        if (level == 0)
        {
            return tMin;
        }


        Vector3D intersectionPoint;
        temp.assign_func(ray.ray_direction.mul_func(tMin));
        intersectionPoint.assign_func(ray.ray_start.add_func(temp));
        Color intersectionPointColor = Object::color;


        Vector3D normal;
        temp.assign_func(b.sub_func(a));
        temp2.assign_func(c.sub_func(a));
        normal.assign_func(temp.cross_func(temp2));
        normal.normalize();

        temp.assign_func(ray.ray_direction.mul_func(-1.0));
        double dot_val = temp.dot_func(normal);
        if (dot_val <= 0.0)
        {
            normal.assign_func(normal.mul_func(-1.0));
        }

        ambientComputation(color,intersectionPointColor);

        for (int i = 0; i < lights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(lights[i].light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(lights[i].light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));//

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,lights[i]);
        }

        for (int i = 0; i < spotLights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(spotLights[i].point_light.light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(spotLights[i].point_light.light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            Vector3D v;
            temp.x = spotLights[i].light_direction.x;
            temp.y = spotLights[i].light_direction.y;
            temp.z = spotLights[i].light_direction.z;
            temp.normalize();
            //spotLights[i].light_direction.normalize();
            double angle = v.getAngle(incidentRay.ray_direction,temp);

            if (angle > (spotLights[i].cutoff_angle * ((pi*1.0)/180.0)))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,spotLights[i].point_light);
        }

        if (level >= recursion_level)
            return tMin;


        Vector3D reflectionDirection;
        double dir_normal_dot_val;
        dir_normal_dot_val = ray.ray_direction.dot_func(normal);
        dir_normal_dot_val = dir_normal_dot_val*2.0;
        temp.assign_func(normal.mul_func(dir_normal_dot_val));
        reflectionDirection.assign_func(ray.ray_direction.sub_func(temp));
        reflectionDirection.normalize();
        Ray reflectedRay;
        reflectedRay.ray_start.assign_func(intersectionPoint.add_func(reflectionDirection));
        reflectedRay.ray_direction.assign_func(reflectionDirection);
        reflectedRay.ray_direction.normalize();


        int nearest = int_inf;
        double t;
        double tMinimum = inf;

        int my_object = 0;
        while(my_object < objects.size())
        {
            Color dcolor;
            t = objects[my_object]->intersect(reflectedRay,dcolor,0);

            if (t > 0.0)
            {
                if ( t < tMinimum)
                {
                    tMinimum = t;
                    nearest = my_object;
                }
            }
            my_object++;
        }


        Color reflectedColor;

        if (nearest != int_inf)
            tMinimum = objects[nearest]->intersect(reflectedRay,reflectedColor,level + 1);


        recursiveRComputation(color,reflectedColor);

        if (color.r > 1.0)
            color.r = 1.0;
        else if (color.r < 0.0)
            color.r = 0.0;

        if (color.g > 1.0)
            color.g = 1.0;
        else if (color.g < 0.0)
            color.g = 0.0;

        if (color.b > 1.0)
            color.b = 1.0;
        else if (color.b < 0.0)
            color.b = 0.0;

        return tMin;
    }

    ~Triangle()
    {
        a.x = 0;
        a.y = 0;
        a.z = 0;
        b.x = 0;
        b.y = 0;
        b.z = 0;
        c.x = 0;
        c.y = 0;
        c.z = 0;
    }
};



class gQuadSurfaceCo
{
public:

    double a,b,c,d,e,f,g,h,i,j;

    gQuadSurfaceCo()
    {
        a = 0.0;
        b = 0.0;
        c = 0.0;
        d = 0.0;
        e = 0.0;
        f = 0.0;
        g = 0.0;
        h = 0.0;
        i = 0.0;
        j = 0.0;
    }

    gQuadSurfaceCo(double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1)
    {
        a = a1;
        b = b1;
        c = c1;
        d = d1;
        e = e1;
        f = f1;
        g = g1;
        h = h1;
        i = i1;
        j = j1;
    }

    ~gQuadSurfaceCo()
    {
        a = 0.0;
        b = 0.0;
        c = 0.0;
        d = 0.0;
        e = 0.0;
        f = 0.0;
        g = 0.0;
        h = 0.0;
        i = 0.0;
        j = 0.0;
    }
};

class generalQuadrics : public Object
{
public:

    gQuadSurfaceCo gen_obj_co;
    Vector3D cubeReferencePoint;
    double length;
    double width;
    double height;

    generalQuadrics()
    {
        gen_obj_co.a = 0.0;
        gen_obj_co.b = 0.0;
        gen_obj_co.c = 0.0;
        gen_obj_co.d = 0.0;
        gen_obj_co.e = 0.0;
        gen_obj_co.f = 0.0;
        gen_obj_co.g = 0.0;
        gen_obj_co.h = 0.0;
        gen_obj_co.i = 0.0;
        gen_obj_co.j = 0.0;
        length = 0.0;
        width = 0.0;
        height = 0.0;
    }

    generalQuadrics(gQuadSurfaceCo gen_obj_co1, Vector3D cubeReferencePoint1, double length1, double width1, double height1)
    {
        gen_obj_co = gen_obj_co1;
        cubeReferencePoint = cubeReferencePoint1;
        length = length1;
        width = width1;
        height = height1;
    }

    void draw()
    {

    }

    double intersect(Ray ray, Color &color, int level)
    {
        Vector3D temp;
        double a,b,c;
        double tMin;
        double tMax;

        a = gen_obj_co.a * ray.ray_direction.x * ray.ray_direction.x;
        a = a + gen_obj_co.b * ray.ray_direction.y * ray.ray_direction.y;
        a = a + gen_obj_co.c * ray.ray_direction.z * ray.ray_direction.z;
        a = a + gen_obj_co.d * ray.ray_direction.x * ray.ray_direction.y;
        a = a + gen_obj_co.e * ray.ray_direction.x * ray.ray_direction.z;
        a = a + gen_obj_co.f * ray.ray_direction.y * ray.ray_direction.z;
        b = 2.0 * gen_obj_co.a * ray.ray_start.x * ray.ray_direction.x;
        b = b + 2.0 * gen_obj_co.b * ray.ray_start.y * ray.ray_direction.y;
        b = b + 2.0 * gen_obj_co.c * ray.ray_start.z * ray.ray_direction.z;
        b = b + gen_obj_co.d * (ray.ray_start.x * ray.ray_direction.y + ray.ray_direction.x * ray.ray_start.y);
        b = b + gen_obj_co.e * (ray.ray_start.x * ray.ray_direction.z + ray.ray_direction.x * ray.ray_start.z);
        b = b + gen_obj_co.f * (ray.ray_start.y * ray.ray_direction.z + ray.ray_direction.y * ray.ray_start.z);
        b = b + gen_obj_co.g * ray.ray_direction.x;
        b = b + gen_obj_co.h * ray.ray_direction.y;
        b = b + gen_obj_co.i * ray.ray_direction.z;
        c = gen_obj_co.a * ray.ray_start.x * ray.ray_start.x;
        c = c + gen_obj_co.b * ray.ray_start.y * ray.ray_start.y;
        c = c + gen_obj_co.c * ray.ray_start.z * ray.ray_start.z;
        c = c + gen_obj_co.d * ray.ray_start.x * ray.ray_start.y;
        c = c + gen_obj_co.e * ray.ray_start.x * ray.ray_start.z;
        c = c + gen_obj_co.f * ray.ray_start.y * ray.ray_start.z;
        c = c + gen_obj_co.g * ray.ray_start.x;
        c = c + gen_obj_co.h * ray.ray_start.y;
        c = c + gen_obj_co.i * ray.ray_start.z + gen_obj_co.j;

        if (a == 0.0)
        {
            if (b == 0.0)
            {
                tMin = inf;
            }
            else
            {
                tMin = -(c/b);
            }
            tMax = inf;
        }
        else
        {
            double discriminant;
            discriminant = b*b - 4.0*a*c;

            if (discriminant < 0.0)
            {
                tMin = inf;
                tMax = inf;
            }
            else if (discriminant > 0.0)
            {
                tMax = (-b+sqrt(discriminant))/(2.0*a);
                tMin = (-b-sqrt(discriminant))/(2.0*a);
            }
            else
            {
                tMin = -b/(2.0*a);
                tMax = inf;
            }
        }


        if (tMin < inf)
        {
            if (tMax < inf)
            {
                if (tMin > 0.0)
                {
                    Vector3D intersectionPoint;
                    temp.assign_func(ray.ray_direction.mul_func(tMin));
                    intersectionPoint.assign_func(ray.ray_start.add_func(temp));

                    bool cond_1 = (length != 0.0);
                    bool cond_2 = (intersectionPoint.x < cubeReferencePoint.x);
                    bool cond_3 = (intersectionPoint.x > cubeReferencePoint.x + length);
                    bool cond_4 = (cond_1 && (cond_2 || cond_3));
                    bool cond_5 = (width != 0.0);
                    bool cond_6 = (intersectionPoint.y < cubeReferencePoint.y);
                    bool cond_7 = (intersectionPoint.y > cubeReferencePoint.y + width);
                    bool cond_8 = (cond_5 && (cond_6 || cond_7));
                    bool cond_9 = (height != 0.0);
                    bool cond_10 = (intersectionPoint.z < cubeReferencePoint.z);
                    bool cond_11 = (intersectionPoint.z > cubeReferencePoint.z + height);
                    bool cond_12 = (cond_9 && (cond_10 || cond_11));
                    if (cond_4 || cond_8 || cond_12)
                    {
                        tMin = inf;
                    }
                }
                if (tMax > 0.0)
                {
                    Vector3D intersectionPoint;
                    temp.assign_func(ray.ray_direction.mul_func(tMax));
                    intersectionPoint.assign_func(ray.ray_start.add_func(temp));

                    bool cond_1 = (length != 0.0);
                    bool cond_2 = (intersectionPoint.x < cubeReferencePoint.x);
                    bool cond_3 = (intersectionPoint.x > cubeReferencePoint.x + length);
                    bool cond_4 = (cond_1 && (cond_2 || cond_3));
                    bool cond_5 = (width != 0.0);
                    bool cond_6 = (intersectionPoint.y < cubeReferencePoint.y);
                    bool cond_7 = (intersectionPoint.y > cubeReferencePoint.y + width);
                    bool cond_8 = (cond_5 && (cond_6 || cond_7));
                    bool cond_9 = (height != 0.0);
                    bool cond_10 = (intersectionPoint.z < cubeReferencePoint.z);
                    bool cond_11 = (intersectionPoint.z > cubeReferencePoint.z + height);
                    bool cond_12 = (cond_9 && (cond_10 || cond_11));
                    if (cond_4 || cond_8 || cond_12)
                    {
                        tMax = inf;
                    }
                }
                if (!(tMin > 0.0 && tMin < tMax))
                {
                    tMin = tMax;
                }
            }
            else
            {
                if (tMin > 0.0)
                {
                    Vector3D intersectionPoint;
                    temp.assign_func(ray.ray_direction.mul_func(tMin));
                    intersectionPoint.assign_func(ray.ray_start.add_func(temp));

                    bool cond_1 = (length != 0.0);
                    bool cond_2 = (intersectionPoint.x < cubeReferencePoint.x);
                    bool cond_3 = (intersectionPoint.x > cubeReferencePoint.x + length);
                    bool cond_4 = (cond_1 && (cond_2 || cond_3));
                    bool cond_5 = (width != 0.0);
                    bool cond_6 = (intersectionPoint.y < cubeReferencePoint.y);
                    bool cond_7 = (intersectionPoint.y > cubeReferencePoint.y + width);
                    bool cond_8 = (cond_5 && (cond_6 || cond_7));
                    bool cond_9 = (height != 0.0);
                    bool cond_10 = (intersectionPoint.z < cubeReferencePoint.z);
                    bool cond_11 = (intersectionPoint.z > cubeReferencePoint.z + height);
                    bool cond_12 = (cond_9 && (cond_10 || cond_11));
                    if (cond_4 || cond_8 || cond_12)
                    {
                        tMin = inf;
                    }
                }
            }
        }

        if (level == 0)
        {
            return tMin;
        }


        Vector3D intersectionPoint;
        temp.assign_func(ray.ray_direction.mul_func(tMin));
        intersectionPoint.assign_func(ray.ray_start.add_func(temp));
        Color intersectionPointColor;
        intersectionPointColor = Object::color;


        double xNormal;
        double yNormal;
        double zNormal;
        double multiplier = 2.0;

        xNormal = (multiplier * gen_obj_co.a * intersectionPoint.x) + (gen_obj_co.d * intersectionPoint.y);
        xNormal = xNormal + (gen_obj_co.e * intersectionPoint.z) + gen_obj_co.g;
        yNormal = (multiplier * gen_obj_co.b * intersectionPoint.y) + (gen_obj_co.d * intersectionPoint.x);
        yNormal = yNormal + (gen_obj_co.f * intersectionPoint.z) + gen_obj_co.h;
        zNormal = (multiplier * gen_obj_co.c * intersectionPoint.z) + (gen_obj_co.e * intersectionPoint.x);
        zNormal = zNormal + (gen_obj_co.f * intersectionPoint.y) + gen_obj_co.i;

        Vector3D normal;
        normal.x = xNormal;
        normal.y = yNormal;
        normal.z = zNormal;
        normal.normalize();

        temp.assign_func(ray.ray_direction.mul_func(-1.0));
        double dot_val = temp.dot_func(normal);
        if (dot_val <= 0.0)
        {
            normal.assign_func(normal.mul_func(-1.0));
        }



        ambientComputation(color, intersectionPointColor);

        for (int i = 0; i < lights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(lights[i].light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(lights[i].light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,lights[i]);
        }

        for (int i = 0; i < spotLights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(spotLights[i].point_light.light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(spotLights[i].point_light.light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            Vector3D v;
            temp.x = spotLights[i].light_direction.x;
            temp.y = spotLights[i].light_direction.y;
            temp.z = spotLights[i].light_direction.z;
            temp.normalize();
            //spotLights[i].light_direction.normalize();
            double angle = v.getAngle(incidentRay.ray_direction,temp);

            if (angle > (spotLights[i].cutoff_angle * ((pi*1.0)/180.0)))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,spotLights[i].point_light);
        }

        if (level >= recursion_level)
        {
            return tMin;
        }

        Vector3D reflectionDirection;
        double dir_normal_dot_val;
        dir_normal_dot_val = ray.ray_direction.dot_func(normal);
        dir_normal_dot_val = dir_normal_dot_val*2.0;
        temp.assign_func(normal.mul_func(dir_normal_dot_val));
        reflectionDirection.assign_func(ray.ray_direction.sub_func(temp));
        reflectionDirection.normalize();
        Ray reflectedRay;
        reflectedRay.ray_start.assign_func(intersectionPoint.add_func(reflectionDirection));
        reflectedRay.ray_direction.assign_func(reflectionDirection);
        reflectedRay.ray_direction.normalize();


        int nearest = int_inf;
        double t;
        double tMinimum = inf;

        int my_object = 0;
        while(my_object < objects.size())
        {
            Color dcolor;
            t = objects[my_object]->intersect(reflectedRay,dcolor,0);

            if (t > 0.0)
            {
                if ( t < tMinimum)
                {
                    tMinimum = t;
                    nearest = my_object;
                }
            }
            my_object++;
        }


        Color reflectedColor;

        if (nearest != int_inf)
            tMinimum = objects[nearest]->intersect(reflectedRay,reflectedColor,level + 1);


        recursiveRComputation(color,reflectedColor);

        if (color.r > 1.0)
            color.r = 1.0;
        else if (color.r < 0.0)
            color.r = 0.0;

        if (color.g > 1.0)
            color.g = 1.0;
        else if (color.g < 0.0)
            color.g = 0.0;

        if (color.b > 1.0)
            color.b = 1.0;
        else if (color.b < 0.0)
            color.b = 0.0;

        return tMin;
    }

    ~generalQuadrics()
    {
        gen_obj_co.a = 0.0;
        gen_obj_co.b = 0.0;
        gen_obj_co.c = 0.0;
        gen_obj_co.d = 0.0;
        gen_obj_co.e = 0.0;
        gen_obj_co.f = 0.0;
        gen_obj_co.g = 0.0;
        gen_obj_co.h = 0.0;
        gen_obj_co.i = 0.0;
        gen_obj_co.j = 0.0;
        length = 0.0;
        width = 0.0;
        height = 0.0;
    }
};


class Floor : public Object
{
public:

    double fWidth;
    double tWidth;
    Color gColor;

    Floor()
    {
        fWidth = 0.0;
        tWidth = 0.0;
        gColor.r = 0.0;
        gColor.g = 0.0;
        gColor.b = 0.0;
    }

    Floor(double fWidth1, double tWidth1, Color gColor1)
    {
        fWidth = fWidth1;
        tWidth = tWidth1;
        gColor = gColor1;
    }

    void draw()
    {
        int i,j,row,col;
        i = 0;
        j = 0;
        row = (int)(fWidth/tWidth);
        col = (int)(fWidth/tWidth);

        while(i < row)
        {
            while(j < col)
            {
                double c_red,c_green,c_blue;
                if( (i + j) % 2 == 0)
                {
                    c_red = Object::color.r;
                    c_green = Object::color.g;
                    c_blue = Object::color.b;
                }
                else
                {
                    c_red = gColor.r;
                    c_green = gColor.g;
                    c_blue = gColor.b;
                }
                glColor3f(c_red,c_green,c_blue);

                Vector3D lb;
                lb.x = (-fWidth/2.0+tWidth*j);
                lb.y = (-fWidth/2.0+tWidth*i);
                lb.z = 0.0;

                glBegin(GL_QUADS);
                {
                    glVertex3f(lb.x, lb.y, lb.z);
                    glVertex3f(lb.x + tWidth, lb.y, lb.z);
                    glVertex3f(lb.x + tWidth, lb.y + tWidth, lb.z);
                    glVertex3f(lb.x, lb.y + tWidth, lb.z);
                }
                glEnd();
                j++;
            }
            i++;
            j = 0;
        }
    }

    double intersect(Ray ray, Color &color, int level)
    {
        Vector3D temp;
        Vector3D normal;
        normal.z = 1.0;
        double dot_val;
        dot_val = position.dot_func(normal);
        if( dot_val <= 0.0)
        {
            normal.z = -1.0;
        }

        double tMin;
        tMin = inf;

        dot_val = normal.dot_func(ray.ray_direction);
        if (dot_val != 0.0)
        {
            double nr_ray_o_dot_val;
            double nr_ray_d_dot_val;
            nr_ray_o_dot_val = normal.dot_func(ray.ray_start);
            nr_ray_d_dot_val = normal.dot_func(ray.ray_direction);
            tMin = (nr_ray_o_dot_val/nr_ray_d_dot_val)*(-1.0);
        }

        if (tMin > 0.0)
        {
            if (tMin < inf)
            {
                Vector3D intersectionPoint;
                temp.assign_func(ray.ray_direction.mul_func(tMin));
                intersectionPoint.assign_func(ray.ray_start.add_func(temp));

                bool cond_1 = (intersectionPoint.x > (-fWidth/2.0));
                bool cond_2 = (intersectionPoint.x < (fWidth/2.0));
                bool cond_3 = (intersectionPoint.y > (-fWidth/2.0));
                bool cond_4 = (intersectionPoint.y < (fWidth/2.0));
                if (!(cond_1 && cond_2 && cond_3 && cond_4))
                {
                    tMin = inf;
                }
            }
        }

        if (level == 0)
        {
            return tMin;
        }

        Vector3D intersectionPoint;
        temp.assign_func(ray.ray_direction.mul_func(tMin));
        intersectionPoint.assign_func(ray.ray_start.add_func(temp));

        double val = -fWidth/2.0;
        temp.x = val;
        temp.y = val;
        temp.z = 0.0;
        Vector3D referencePosition;
        referencePosition.assign_func(intersectionPoint.sub_func(temp));
        Color intersectionPointColor;
        double x_val,y_val;
        x_val = floor(referencePosition.x/tWidth);
        y_val = floor(referencePosition.y/tWidth);
        int tile_number = ((int)(x_val + y_val));
        if ( tile_number % 2 == 0)
        {
            intersectionPointColor = Object::color;
        }
        else
        {
            intersectionPointColor = gColor;
        }

        ambientComputation(color,intersectionPointColor);

        for (int i = 0; i < lights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(lights[i].light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(lights[i].light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));//

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,lights[i]);
        }

        for (int i = 0; i < spotLights.size(); i++)
        {
            double ep;
            ep = 0.0000001;
            Ray incidentRay;
            incidentRay.ray_start.assign_func(spotLights[i].point_light.light_pos);
            incidentRay.ray_direction.assign_func(intersectionPoint.sub_func(spotLights[i].point_light.light_pos));
            incidentRay.ray_direction.normalize();


            double t;
            double tMinimum;
            tMinimum = inf;

            int object_no = 0;
            while(object_no < objects.size())
            {
                Color d_color;
                t = objects[object_no]->intersect(incidentRay,d_color,0);

                if (t > 0.0)
                {
                    if (t < tMinimum)
                    {
                        tMinimum = t;
                    }
                }
                object_no++;
            }

            Vector3D shadowIP;
            temp.assign_func(incidentRay.ray_direction.mul_func(tMinimum));
            shadowIP.assign_func(incidentRay.ray_start.add_func(temp));

            if (intersectionPoint.vec_distance(incidentRay.ray_start) - ep > shadowIP.vec_distance(incidentRay.ray_start))
                continue;

            Vector3D v;
            temp.x = spotLights[i].light_direction.x;
            temp.y = spotLights[i].light_direction.y;
            temp.z = spotLights[i].light_direction.z;
            temp.normalize();
            //spotLights[i].light_direction.normalize();
            double angle = v.getAngle(incidentRay.ray_direction,temp);

            if (angle > (spotLights[i].cutoff_angle * ((pi*1.0)/180.0)))
                continue;

            reflectionComputation(ray,incidentRay,normal,color,intersectionPoint,intersectionPointColor,spotLights[i].point_light);
        }

        if (level >= recursion_level)
            return tMin;


        Vector3D reflectionDirection;
        double dir_normal_dot_val;
        dir_normal_dot_val = ray.ray_direction.dot_func(normal);
        dir_normal_dot_val = dir_normal_dot_val*2.0;
        temp.assign_func(normal.mul_func(dir_normal_dot_val));
        reflectionDirection.assign_func(ray.ray_direction.sub_func(temp));
        reflectionDirection.normalize();
        Ray reflectedRay;
        reflectedRay.ray_start.assign_func(intersectionPoint.add_func(reflectionDirection));
        reflectedRay.ray_direction.assign_func(reflectionDirection);
        reflectedRay.ray_direction.normalize();


        int nearest = int_inf;
        double t;
        double tMinimum = inf;

        int my_object = 0;
        while(my_object < objects.size())
        {
            Color dcolor;
            t = objects[my_object]->intersect(reflectedRay,dcolor,0);

            if (t > 0.0)
            {
                if ( t < tMinimum)
                {
                    tMinimum = t;
                    nearest = my_object;
                }
            }
            my_object++;
        }


        Color reflectedColor;

        if (nearest != int_inf)
            tMinimum = objects[nearest]->intersect(reflectedRay,reflectedColor,level + 1);


        recursiveRComputation(color,reflectedColor);

        if (color.r > 1.0)
            color.r = 1.0;
        else if (color.r < 0.0)
            color.r = 0.0;

        if (color.g > 1.0)
            color.g = 1.0;
        else if (color.g < 0.0)
            color.g = 0.0;

        if (color.b > 1.0)
            color.b = 1.0;
        else if (color.b < 0.0)
            color.b = 0.0;

        return tMin;
    }

    ~Floor()
    {
        fWidth = 0.0;
        tWidth = 0.0;
        gColor.r = 0.0;
        gColor.g = 0.0;
        gColor.b = 0.0;
    }
};

