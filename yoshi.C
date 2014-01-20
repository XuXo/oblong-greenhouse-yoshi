//tian
#include "Greenhouse.h"

using namespace std;

//#define VERBOSE
//#define DEBUG2

class Yoshi : public Image
{
public:
    
    Vect velocity;
    
    //elapsed_time is used to keep count of number of iterations of travail(), ideally we could find the distance btw Yoshi and the destination in real time and
    //find a new neighbor when the distance gets arbitrarily small but this requires that the Yoshi class be independent and move like the cube is moving( as opposed
    //to right now where Yoshi is appended to the cube and goes along for the ride...)
    static float elapsed_time;
    
    vector<pair<Vect,int> > point0_neighbors, point1_neighbors, point2_neighbors, point3_neighbors, point4_neighbors, point5_neighbors, point6_neighbors, point7_neighbors, point8_neighbors;
    vector<vector<pair<Vect,int> > > lattice;
    int cur_loc;
    Vect dir;
    
    Yoshi() : Image("images/yoshi/yoshi.png") {
        
        //our initial selection, so starting from corner 1 this will go to corner 2, from here on out selection will be random
        dir = Vect(0,0,-.1);
        
        velocity = Vect(1.0, 1.0, 1.0);
        velocity /= velocity.DistFrom(ZeroVect);
        SetSize(20.0);
        SetName("Yoshi");
        //SetTranslationHard(Vect(Random(-20.0, 20.0), Random(-20.0, 20.0), 0.0));
        SlapOnFeld();
        
        SetTranslation(Vect(-15,15,15));        //starting at corner 1, refer to diagram below
        cur_loc = 2;                            //determined by our choice of "dir" above
        
        
        //point_neighbors refer to list of adjacent corners from current position, the 2nd index in the pair indicates the corner number which needs to be
        //updated on each iteration, refer to the diagram
        
        point0_neighbors.push_back(make_pair(Vect(0,0,-.1),2));
        point0_neighbors.push_back(make_pair(Vect(.1,0,0),4));
        point0_neighbors.push_back(make_pair(Vect(0,-.1,0),5));
        lattice.push_back(point0_neighbors);
        
        point1_neighbors.push_back(make_pair(Vect(0,0,-.1),2));
        point1_neighbors.push_back(make_pair(Vect(.1,0,0),4));
        point1_neighbors.push_back(make_pair(Vect(0,-.1,0),5));
        lattice.push_back(point1_neighbors);
        
        point2_neighbors.push_back(make_pair(Vect(.1,0,0),3));
        point2_neighbors.push_back(make_pair(Vect(0,0,.1),1));
        point2_neighbors.push_back(make_pair(Vect(0,-.1,0),6));
        lattice.push_back(point2_neighbors);
        
        point3_neighbors.push_back(make_pair(Vect(0,0,.1),4));
        point3_neighbors.push_back(make_pair(Vect(-.1,0,0),2));
        point3_neighbors.push_back(make_pair(Vect(0,-.1,0),7));
        lattice.push_back(point3_neighbors);
        
        point4_neighbors.push_back(make_pair(Vect(-.1,0,0),1));
        point4_neighbors.push_back(make_pair(Vect(0,0,-.1),3));
        point4_neighbors.push_back(make_pair(Vect(0,-.1,0),8));
        lattice.push_back(point4_neighbors);
        
        point5_neighbors.push_back(make_pair(Vect(.1,0,0),8));
        point5_neighbors.push_back(make_pair(Vect(0,0,-.1),6));
        point5_neighbors.push_back(make_pair(Vect(0,.1,0),1));
        lattice.push_back(point5_neighbors);
        
        point6_neighbors.push_back(make_pair(Vect(0,0,.1),5));
        point6_neighbors.push_back(make_pair(Vect(.1,0,0),7));
        point6_neighbors.push_back(make_pair(Vect(0,.1,0),2));
        lattice.push_back(point6_neighbors);
        
        point7_neighbors.push_back(make_pair(Vect(-.1,0,0),6));
        point7_neighbors.push_back(make_pair(Vect(0,0,.1),8));
        point7_neighbors.push_back(make_pair(Vect(0,.1,0),3));
        lattice.push_back(point7_neighbors);
        
        point8_neighbors.push_back(make_pair(Vect(0,0,-.1),7));
        point8_neighbors.push_back(make_pair(Vect(-.1,0,0),5));
        point8_neighbors.push_back(make_pair(Vect(0,.1,0),4));
        lattice.push_back(point8_neighbors);
        
    }
    
    void Travail() {
        //Vect v = Find<Text>("try") ->Translation();
        //cout<<v<<endl;
        
        
        //Vect direction = bb-aa;
        //cout<<direction<<endl;
        
        //IncTranslation(direction/100.00);
        IncTranslation(dir);
        
        #ifdef DEBUG2
        INFORM ("currently located at " +ToStr ( WrangleLoc (Vect (0, 0, 0))));
        cout<<endl<<endl;
        #endif
        
        Vect b(-15,15,-15);
        //if((UnWrangleLoc (Vect (0, 0, 0))).DistFrom(bb) < 1)
        //IncTranslation(Vect(100,100,100));
        
        elapsed_time += .1;
        
        #ifdef DEBUG2
        cout<<"elapsed time is"<<elapsed_time<<endl;
        cout<<"elapsed time int is"<<(int)elapsed_time<<endl;
        cout<<"difference btw float and int is"<<(elapsed_time - (int)elapsed_time)<<endl;
        #endif
        
        if((elapsed_time - (int)elapsed_time) < .1)
        {
            int time = (int)elapsed_time;
            
            //cube is 30 mm in dimension, so at .1mm per call it will take 300 iterations which we keep track of with the elapsed_time parameter, this is considered
            //cheating but the alternative which is to not have Yoshi appended to Cube is costly and inaccurate.  I could not find a way to get the direction vector
            //which is in constant flux properly with WrangleLoc()
            if( time % 30 == 0)
            {
                int new_loc = Random(3);        //one third probability of choosing any one of its three adjacent edges
                vector<pair<Vect,int> >corner = lattice[cur_loc];
                pair<Vect,int> new_pair = corner[new_loc];
                int new_corner = new_pair.second;
                Vect new_dir = new_pair.first;
                
                #ifdef VERBOSE
                cout<<"new corner is "<<new_corner<<endl;
                INFORM("new vector is" +ToStr (new_dir));
                cout<<"I chose edge number "<<new_loc<<endl;
                #endif
                
                cur_loc = new_corner;
                dir = new_dir;
            }
        }
    }
};



class Cube : public Thing
{
    
public:
    
    Image *corner_1, *corner_2, *corner_3, *corner_4, *corner_5, *corner_6, *corner_7, *corner_8;
    Vect velocity;
    Trove <Vect> opengl_lines;
    float64 desired_rotation;
    int random_mod3 = 1;
    float64 a,b,c;
    
    Cube () : Thing ()
    {
		//the cube is constructed from a series of points(Vect) and plotted via openGL but the corners are used for identification by the moving Yoshi
        //This is just for my own benefit, you could do create the corners like below and track it but travail() seems to experiene a bit of lag and Yoshi
        //would veer off the edge occasionally but readjust on the next turning point
        
        /*corner_1= new Image("images/yoshi/egg.png");
        corner_1->SetHeightUniformly(1.0);
        corner_1->SetName("corner_1");
        corner_1->SetTranslation(Vect(-15,15,15));
        
        corner_2= new Image("images/yoshi/egg.png");
        corner_2->SetHeightUniformly(1.0);
        corner_2->SetName("corner_2");
        corner_2->SetTranslation(Vect(-15,15,-15));
        
        corner_3= new Image("images/yoshi/egg.png");
        corner_3->SetHeightUniformly(1.0);
        corner_3->SetName("corner_3");
        corner_3->SetTranslation(Vect(15,15,-15));
        
        corner_4= new Image("images/yoshi/egg.png");
        corner_4->SetHeightUniformly(1.0);
        corner_4->SetName("corner_4");
        corner_4->SetTranslation(Vect(15,15,15));
        
        corner_5= new Image("images/yoshi/egg.png");
        corner_5->SetHeightUniformly(1.0);
        corner_5->SetName("corner_5");
        corner_5->SetTranslation(Vect(-15,-15,15));
        
        corner_6= new Image("images/yoshi/egg.png");
        corner_6->SetHeightUniformly(1.0);
        corner_6->SetName("corner_6");
        corner_6->SetTranslation(Vect(-15,-15,-15));
        
        corner_7= new Image("images/yoshi/egg.png");
        corner_7->SetHeightUniformly(1.0);
        corner_7->SetName("corner_7");
        corner_7->SetTranslation(Vect(15,-15,-15));
        
        corner_8= new Image("images/yoshi/egg.png");
        corner_8->SetHeightUniformly(1.0);
        corner_8->SetName("corner_8");
        corner_8->SetTranslation(Vect(15,-15,15));
        
		SetName("cube");
        */
        
        /*for (int i = 0  ;  i < 20  ;  i++)
         opengl_lines . Append (Vect (Random (-50, 50),
         Random (-50, 50),
         Random (-50, 50)));*/
        
		//		    2---------------3
		//		   /|		       /|					(-15,15,-15)				(15,15,-15)
		//		  / |		      / |
		//		 /  |			 /  |
		//	    1---------------4   |			(-15,15,15)					(15,15,15)
		//		|	|    		|	|
		//      |	|			|	|
		//      |   6-----------|---7
		//		|  /			|  /					(-15,-15,-15)				(15,-15,-15)
		//		| /				| /
		//		|/              |/
		//		5---------------8				(-15,-15,15)				(15,-15,15)
        
        
        
		//(12) will denote the vector from 1 to 2 and (21) the opposite orientation
		// (12) cross (14) , negative
		// (15) cross (12)
		// (58) cross (51)
        
        //using trove didnt work
        //Trove<Vect> x;
        //x.Append(Vect(15,15,15));
        //SetName("dest_point");
        
        //using image didnt work either
        //Image x("images/pong/ball.png");
        
        
        
        Text *t = new Text ("Yoshi's Dilemma");
        t->SetName("try");
        t -> SlapOnFeld ();
        t->IncTranslation(Vect(0,50,0));
        
        
        Vect point1(-15,15,15);
        SetName("point1");
        Vect point2(-15,15,-15);
        Vect point3(15,15,-15);
        Vect point4(15,15,15);
        Vect point5(-15,-15,15);
        Vect point6(-15,-15,-15);
        Vect point7(15,-15,-15);
        Vect point8(15,-15,15);
        
        opengl_lines.Append(point8);
        opengl_lines.Append(point7);
        opengl_lines.Append(point6);
        opengl_lines.Append(point5);
        opengl_lines.Append(point8);
        
        opengl_lines.Append(point4);
        opengl_lines.Append(point3);
        opengl_lines.Append(point2);
        opengl_lines.Append(point1);
        opengl_lines.Append(point4);
        
        opengl_lines.Append(point3);
        opengl_lines.Append(point7);
        opengl_lines.Append(point6);
        opengl_lines.Append(point2);
        opengl_lines.Append(point1);
        opengl_lines.Append(point5);
        
        //IncTranslation(Vect(-100,-100,30));
        
        
        
		//given the 8 points, we can determine all the edges and take the cross product btw 2 adjacent to find the normal vector of that plane, this is essentially the vector needed below
        
		//give a plane ax + by + cz + d = 0, and a point (x0,y0, z0) we can find the min distance between the point and the plane as
		//|ax0 + by0 + cz0 + d| / sqrt(a^2 + b^2 + c^2)
		//so we calculate the min distance btw the ball and each of the 6 faces, the min will determine the face of interest, from which we can use the normal vector to find
		//how it should be deflected
        
		//realize we really need the distance btw the ball and a face, which is only a subsection of a plane, supposition being with regard to an infinite plane the minimal distance could
		//miss the cube altogether if they were far to begin with, consider the situation
		
		//									O (ball)
		//	 ___________
		//	/__________/
		//notice the orthogonal distance in this case is very small but in fact we really need the distance from the ball to the edge of the face which is much larger,
        
		
		//but notice if we start the ball in the cube this should never be a problem since when the ball gets close enough to the edge we should be able to capture it and bounce it back,
		//ie it should always remain within the inifnite rectangular projection of the plane in the direction of interest.  I just realized if we just append this at a child of the cube none of this may be necessary..
        
        
        
    }
    
    void Travail () {
        //cout<<"location of point 1 is "<<Find<>("point1")->Translation();
        
        float64 time_to_rotate = Random(10);
        
        #ifdef DEBUG2
        cout<<"time to rotate is" <<time_to_rotate<<endl;
        #endif
        
		//to get a somewhat uniformly random rotating cube, we change the axis of rotation constantly and weight it heavily towards two of three components
        //there's a much better way of doing this I'm sure.  We choose 10% chance of rotating on each frame for a less fidgity simulation
        if(time_to_rotate > 9) {
            random_mod3 = (random_mod3 + 1) % 3;
            if(random_mod3 == 0) {
                a = Random(0.0, 10.0);
                b = Random(90.0, 100.0);
                c = Random(90.0, 100.0);
            }
            else if(random_mod3 == 1) {
                b = Random(0.0, 10.0);
                a = Random(90.0, 100.0);
                c = Random(90.0, 100.0);
            }
            else {
                c = Random(0.0, 10.0);
                a = Random(90.0, 100.0);
                b = Random(90.0, 100.0);
            }
        }
        
        IncRotation (Vect (a,b,c),.01);
        //so just rotation doesn't change the loc since its fixed at the center
        //IncTranslation(Vect(1,1,1));
        //cout<<"current position is"<< Translation()<<endl;
        
        #ifdef DEBUG2
        INFORM ("Time since last travail = " + ToStr (TimeSinceLastTravail ()) + "ms");
        INFORM ("FPS () is " + ToStr (FPS ()));
        #endif
        /*
        corner_1 -> IncRotation (Vect (1,2,3),.01);
        corner_2 -> IncRotation (Vect (1,2,3),.01);
        */
        
        
        /*
         //INFORM ("corner1 loc with unwrangleloc = " +ToStr ( corner_1 -> UnWrangleLoc (Vect (0, 0, 0))));
         INFORM ("corner1 loc with wrangleloc = " +ToStr ( corner_1 -> WrangleLoc (Vect (0, 0, 0))));
         
         //INFORM ("corner2 loc with unwrangleloc = " +ToStr ( corner_2 -> UnWrangleLoc (Vect (0, 0, 0))));
         INFORM ("corner2 loc with wrangleloc = " +ToStr ( corner_2 -> WrangleLoc (Vect (0, 0, 0))));
         cout<<endl;
         //IncTranslation(velocity);
         
         //Distance(   corner_1 -> WrangleLoc (Vect (0, 0, 0)), corner_2 -> WrangleLoc (Vect (0, 0, 0))  );
         Vect a = corner_1 -> WrangleLoc (Vect (0, 0, 0));
         Vect b = corner_2 -> WrangleLoc (Vect (0, 0, 0));
         float64 dist = a.DistFrom(b);
         cout<<dist<<endl;
         */
        
    }
    
    
    void PointingHarden (PointingEvent *e) {
        desired_rotation = Random (PI * 2, PI * 6);
        //SetRotation (Vect (0, 0, 1), desired_rotation);
        IncRotation (Vect (1, 0, 0), desired_rotation);
        //IncRotationHard (Vect (0, 0, 1), desired_rotation);
    }
    
    virtual void PreDraw () {
        //glLineWidth(2.0);
    }
    
    void DrawSelf () {
        SetGLColor (Color (0, 1, 0));
        glBegin(GL_LINES);
        for (int i = 0; i < opengl_lines.Count() - 1; i++) {
            Vect line_start = opengl_lines.Nth (i);
            glVertex (line_start);
            Vect line_stop = opengl_lines.Nth (i+1);
            glVertex (line_stop);
        }
        glEnd();
    }
    
    void PostDraw () {
        //glLineWidth(1.0);
    }
};


float Yoshi::elapsed_time = 0;

void Setup () {
    
    Image *corner1 = new Image("images/yoshi/egg.png");
    corner1->SetSize(5.0);
    corner1->SetName("corner1");
    corner1->SetTranslation(Vect(-15,15,15));
    
    Image *corner2 = new Image("images/yoshi/egg.png");
    corner2->SetSize(5.0);
    corner2->SetName("corner2");
    corner2->SetTranslation(Vect(-15,15,-15));
    
    Image *corner3 = new Image("images/yoshi/egg.png");
    corner3->SetSize(5.0);
    corner3->SetName("corner3");
    corner3->SetTranslation(Vect(15,15,-15));
    
    Image *corner4 = new Image("images/yoshi/egg.png");
    corner4->SetSize(5.0);
    corner4->SetName("corner4");
    corner4->SetTranslation(Vect(15,15,15));
    
    Image *corner5 = new Image("images/yoshi/egg.png");
    corner5->SetSize(5.0);
    corner5->SetName("corner5");
    corner5->SetTranslation(Vect(-15,-15,15));
    
    Image *corner6 = new Image("images/yoshi/egg.png");
    corner6->SetSize(5.0);
    corner6->SetName("corner6");
    corner6->SetTranslation(Vect(-15,-15,-15));
    
    Image *corner7 = new Image("images/yoshi/egg.png");
    corner7->SetSize(5.0);
    corner7->SetName("corner7");
    corner7->SetTranslation(Vect(15,-15,-15));
    
    Image *corner8 = new Image("images/yoshi/egg.png");
    corner8->SetSize(5.0);
    corner8->SetName("corner8");
    corner8->SetTranslation(Vect(15,-15,15));
    
    Cube *cube = new Cube ();
    Yoshi *ball = new Yoshi();
    
    cube -> AppendKid(ball);
    cube -> AppendKid(corner1);
    cube -> AppendKid(corner2);
    cube -> AppendKid(corner3);
    cube -> AppendKid(corner4);
    cube -> AppendKid(corner5);
    cube -> AppendKid(corner6);
    cube -> AppendKid(corner7);
    cube -> AppendKid(corner8);
    
    cube -> SlapOnFeld ();
}
