//**************************************************************************
// Práctica 3 
//**************************************************************************

#include "objetos_B3.h"
#include "file_ply_stl.hpp"
#include <time.h> 


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();

}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores( )
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glColor4f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b, colores_caras[i].a);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);break;
	case SOLID_COLORS:draw_solido_colores();break;
	}
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2, float t) // t = transparencia
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
      colores_caras[i].a=t;
     }
   else 
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
      colores_caras[i].a=t;
     } 
  }
}


//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 

//colores de las caras
colors_random();
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
int i;
//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

//colores de las caras
colors_random();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



void _objeto_ply::parametros(char *archivo)
{
int i, n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);
// vértices

for (i=0;i<n_ver;i++)
  {vertices[i].x=ver_ply[3*i];
   vertices[i].y=ver_ply[3*i+1];
   vertices[i].z=ver_ply[3*i+2];
  }

// vértices
for (i=0;i<n_car;i++)
  {caras[i].x=car_ply[3*i];
   caras[i].y=car_ply[3*i+1];
   caras[i].z=car_ply[3*i+2];
  }

// colores
colors_random();
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, 
                           int tapa_in, int tapa_su, int tipo)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio;

// tratamiento de los vértice
radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

num_aux=perfil.size();
if (tipo==2) num_aux=1;
vertices.resize(num_aux*num);

for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 
if (tipo<2)
{
for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+j*num_aux;
      cara_aux._1=i+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
     }
   }
}
 
// tapa inferior
if (tapa_in==1)
{
  // punto central de la tapa
  vertice_aux.x=0.0;
  if (tipo==1) vertice_aux.y=-radio;
  else vertice_aux.y=perfil[0].y;
  vertice_aux.z=0.0;
  vertices.push_back(vertice_aux);
  //caras tapa inferior

  cara_aux._0=num_aux*num;
  for (j=0;j<num;j++)
    {
     cara_aux._1=((j+1)%num)*num_aux;
     cara_aux._2=j*num_aux;
     caras.push_back(cara_aux);
    }

}
 
// tapa superior

if (tapa_su==1)
{
  // punto central de la tapa
  vertice_aux.x=0.0;
  vertice_aux.y=perfil[num_aux-1].y;
  if (tipo==1) vertice_aux.y=radio;
  if (tipo==2) vertice_aux.y=perfil[1].y;
  vertice_aux.z=0.0;
  vertices.push_back(vertice_aux);

  //caras tapa superior
  if (tapa_in==1) cara_aux._0=num_aux*num+1;
  else cara_aux._0=num_aux*num;

  for (j=0;j<num;j++)
    {cara_aux._1=j*num_aux+num_aux-1;
     cara_aux._2=((j+1)%num)*num_aux+num_aux-1;
     caras.push_back(cara_aux);
    }
}

//colores de las caras
colors_random();
}


//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=poligono.size();
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 

caras.resize(num_aux*2);
int c=0;
for (i=0;i<num_aux;i++)         
  {
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;    
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;    
   c=c+1;    
   }  
   
//colores de las caras
colors_random();
}

//************************************************************************
//************************************************************************

//************************************************************************
// objeto cilindro (caso especial de rotacion)
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num)
{
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
  perfil.push_back(aux);
  aux.x=radio; aux.y=altura/2.0; aux.z=0.0;
  perfil.push_back(aux);
  parametros(perfil,num,1,1,0);
}

//************************************************************************
// objeto cono (caso especial de rotacion)
//************************************************************************

_cono::_cono(float radio, float altura, int num)
{
vector<_vertex3f> perfil;
_vertex3f aux;

aux.x=radio; aux.y=0; aux.z=0.0;
perfil.push_back(aux);
aux.x=0.0; aux.y=altura; aux.z=0.0;
perfil.push_back(aux);
parametros(perfil,num,1,1,2);
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
//************************************************************************

_esfera::_esfera(float radio, int latitud, int longitud)
{
vector<_vertex3f> perfil;
_vertex3f aux;
int i;
for (i=1;i<latitud;i++)
  {aux.x=radio*cos(M_PI*i/(latitud*1.0)-M_PI/2.0);
   aux.y=radio*sin(M_PI*i/(latitud*1.0)-M_PI/2.0);
   aux.z=0.0;
   perfil.push_back(aux);
  }
parametros(perfil,longitud,1,1,1);
}


//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************

_rotacion_PLY::_rotacion_PLY()
{

}

void _rotacion_PLY::parametros_PLY(char *archivo, int num)
{

}

//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

_pala::_pala(float radio, float ancho, int num)
{
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int i, j;

  vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
  perfil.push_back(vertice_aux);
  vertice_aux.z=ancho/2.0;
  perfil.push_back(vertice_aux);

  // tratamiento de los vértices

  for (j=0;j<=num;j++)
    {for (i=0;i<2;i++)	
      {
        vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
                      perfil[i].y*sin(M_PI*j/(1.0*num));
        vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
                      perfil[i].y*cos(M_PI*j/(1.0*num));
        vertice_aux.z=perfil[i].z;
        vertices.push_back(vertice_aux);
      }
    }
    
  // tratamiento de las caras 

  for (j=0;j<num;j++)
    {cara_aux._0=j*2;
      cara_aux._1=(j+1)*2;
      cara_aux._2=(j+1)*2+1;
      caras.push_back(cara_aux);
      
      cara_aux._0=j*2;
      cara_aux._1=(j+1)*2+1;
      cara_aux._2=j*2+1;
      caras.push_back(cara_aux);
    }
    
  // tapa inferior
  vertice_aux.x=0;
  vertice_aux.y=0;
  vertice_aux.z=-ancho/2.0;
  vertices.push_back(vertice_aux); 

  for (j=0;j<num;j++)
    {cara_aux._0=j*2;
      cara_aux._1=(j+1)*2;
      cara_aux._2=vertices.size()-1;
      caras.push_back(cara_aux);
    }
    
  // tapa superior
  vertice_aux.x=0;
  vertice_aux.y=0;
  vertice_aux.z=ancho/2.0;
  vertices.push_back(vertice_aux); 

  for (j=0;j<num;j++)
    {cara_aux._0=j*2+1;
      cara_aux._1=(j+1)*2+1;
      cara_aux._2=vertices.size()-1;
      caras.push_back(cara_aux);
    }
    
  colors_chess(1.0,1.0,0.0,0.0,0.0,1.0,0);
}

//************************************************************************
// brazo
//************************************************************************

_brazo::_brazo()
{
  ancho=0.6;
  alto=0.1;
  fondo=0.1;
  colors_chess(1.0,1.0,0.0,0.0,0.0,1.0,0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  glTranslatef(0.5,0,0);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
  ancho=0.4;
  alto=0.6;
  fondo=0.4;
  cubo.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0,0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion()
{
  ancho=1.2;
  alto=0.3;
  fondo=0.8;
  radio=0.15;
  base.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0,0);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glTranslatef(2*ancho/6,-alto/2.0,0);
  glRotatef(90,1,0,0);
  glScalef(radio, fondo/2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2*ancho/6,-alto/2.0,0);
  glRotatef(90,1,0,0);
  glScalef(radio, fondo/2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora()
{
  giro_cabina = 0.0;
  giro_primer_brazo = 0.0;
  giro_primer_brazo_max = 0;
  giro_primer_brazo_min = -90;
  giro_segundo_brazo = 0.0;
  giro_segundo_brazo_max = 30;
  giro_segundo_brazo_min = 0;
  giro_pala = 0.0;
  giro_pala_max = 50.0;
  giro_pala_min = -90.0;

  tamanio_pala=0.15;
};


void _excavadora::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();

  sustentacion.draw(modo, r, g, b, grosor);

  glTranslatef(0,(cabina.alto+sustentacion.alto)/2.0,0);
  glRotatef(giro_cabina,0,1,0);
  cabina.draw(modo, r, g, b, grosor);

  glTranslatef(cabina.ancho/2.0,0,0);
  glRotatef(giro_segundo_brazo,0,0,1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho,0,0);
  glRotatef(giro_primer_brazo,0,0,1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho,0,0);
  glRotatef(giro_pala,0,0,1);
  glTranslatef(tamanio_pala,0,0); // trasladamos 
  glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
  pala.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

//************************************************************************
// práctica 3, objeto jerárquico articulado: Lavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************


//************************************************************************
// rueda
//************************************************************************
_rueda::_rueda()
{
  ancho_cilindro=0.1;
  alto_cilindro = 0.1;
  fondo_cilindro = 0.1;

  ancho_palo = 0.03;
  alto_palo = 0.1;
  fondo_palo = 0.03;

  ancho_base = 0.1;
  alto_base = 0.01;
  fondo_base = 0.1;

  cilindro.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
  palo.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
  base.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _rueda::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho_cilindro, alto_cilindro, fondo_cilindro);
  glRotatef(90,1,0,0);
  cilindro.draw(modo, 0.2, 0.2, 0.2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,0.15,0);
  glScalef(ancho_palo, alto_palo, fondo_palo);
  palo.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,0.2,0);
  glScalef(ancho_base, alto_base, fondo_base);
  base.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();
};

//************************************************************************
// puerta
//************************************************************************
_puerta::_puerta()
{
  ancho_cilindro=1.6;
  alto_cilindro=0.05;
  fondo_cilindro=1.6;

  ancho_cilindro2=1.3;
  alto_cilindro2=0.05;
  fondo_cilindro2=1.3;

  ancho_cubo=0.15;
  alto_cubo=0.5;
  fondo_cubo=0.15;
  cilindro.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
  cilindro2.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
  cubo.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _puerta::draw(_modo modo, float r, float g, float b, float grosor)
{

  glPushMatrix();
  glTranslatef(2.5,0,0.2);
  glScalef(ancho_cubo, alto_cubo, fondo_cubo);
  cubo.draw(modo,0,0,0, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90,1,0,0);
  glTranslatef(1.5,0.1,0);
  glScalef(ancho_cilindro2, alto_cilindro2, fondo_cilindro2);
  cilindro2.draw(modo, 1, 1, 1, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90,1,0,0);
  glTranslatef(1.5,0,0);
  glScalef(ancho_cilindro, alto_cilindro, fondo_cilindro);
  cilindro.draw(modo, 0.7, 0.7, 0.7, grosor);
  glPopMatrix();

  
};

//************************************************************************
// tambor
//************************************************************************
_tambor::_tambor()
{
  ancho=1.5;
  alto=0.05;
  fondo=1.5;
  cilindro.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _tambor::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glRotatef(90,1,0,0);
  glScalef(ancho, alto, fondo);
  cilindro.draw(modo, 0, 0, 0, grosor);
  glPopMatrix();
};

//************************************************************************
// cajon
//************************************************************************
_cajon::_cajon()
{
  ancho=1.3;
  alto=0.2;
  fondo=2;
  cubo.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _cajon::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, 0.15, 0.15, 0.15, grosor);
  glPopMatrix();

};

//************************************************************************
// boton_apagado
//************************************************************************
_boton_apagado::_boton_apagado()
{
  ancho=3;
  alto=1;
  fondo=3;
  cilindro.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _boton_apagado::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cilindro.draw(modo, r, g, b, grosor);
  glPopMatrix();

};


//************************************************************************
// ruleta
//************************************************************************
_ruleta::_ruleta()
{
  ancho_cilindro=1.5;
  alto_cilindro=0.05;
  fondo_cilindro=1.5;

  ancho_cubo = 0.5;
  alto_cubo = 5;
  fondo_cubo = 1.5;

  cilindro.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
  cubo.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _ruleta::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glRotatef(90,1,0,0);
  glScalef(ancho_cilindro, alto_cilindro, fondo_cilindro);
  cilindro.draw(modo, 0, 0, 0, grosor);

  glTranslatef(0,fondo_cilindro,0);
  glScalef(ancho_cubo, alto_cubo, fondo_cubo);
  cubo.draw(modo, 1, 1, 1, grosor);
  glPopMatrix();
};

//************************************************************************
// cuerpo
//************************************************************************
_cuerpo::_cuerpo()
{
  ancho=4;
  alto=6;
  fondo=4;
  base.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
  cubo_pequeño.colors_chess(0.8,0.8,0.8,0.0,0.0,0.0,1);
};

void _cuerpo::draw(_modo modo, float r, float g, float b, float grosor)
{
  //cubo grande
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, 0.5, 0.5, 0.5, grosor);
  //cubo pequeño
  glScalef(1.0,0.1,0.86);
  glTranslatef(0,5.5,-0.08);
  cubo_pequeño.draw(modo, 0.7, 0.7, 0.7, grosor);
  glPopMatrix();
};

_lavadora::_lavadora()
{
  // posicones
  posicion_cajon = 0.0;
  posicion_lavadora_z=0.0;
  cajon_max = 1.9;
  cajon_min = 0.0;
  // giros
  giro_puerta = 0.0;
  giro_puerta_max = 90.0;
  giro_puerta_min = 0.0;
  giro_tambor = 0.0;
  giro_ruleta1_max = 180.0;
  giro_ruleta1_min = 0.0;
  giro_ruleta2_max = 180.0;
  giro_ruleta2_min = 0.0;
  // color boton apagado
  color_r_boton = 0.5;
  fin_lavado = 450;
};

void _lavadora::draw(_modo modo, float r, float g, float b, float grosor)
{
  // // LAVADORA

   glPushMatrix();
  
   glTranslatef(0,0,posicion_lavadora_z);
    //cuerpo
    glPushMatrix();
    cuerpo.draw(modo, r, g, g, grosor);
    glPopMatrix();
    // cajon
    glPushMatrix();
    glTranslatef(0,0,posicion_cajon);
    glTranslatef(-cajon.ancho + 0.1,3.25,0.5);
    cajon.draw(modo,r,g,b,grosor);
    glPopMatrix();
    // puerta
    glPushMatrix();
    glTranslatef(-1.5,0,2.075);
    glRotatef(-giro_puerta,0,1,0);
    puerta.draw(modo,r,g,b,grosor);
    glPopMatrix();
    // tambor
    glPushMatrix();
    glTranslatef(0,0,1.975);
    glRotatef(-giro_tambor,0,0,1);
    tambor.draw(modo,r,g,b,grosor);
    // comprobaciones para encender la luz
    if(giro_tambor > 1)
      color_r_boton = 1;
    if(giro_tambor > fin_lavado)
      color_r_boton = 0.5;
    glPopMatrix();

    // ruletas
    glPushMatrix();
    glTranslatef(1,3.3,1.475);
    glRotatef(giro_ruleta1, 0,0,1);
    glScalef(0.15,0.15,0.15);
    ruleta1.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,3.3,1.475);
    glRotatef(giro_ruleta2,0,0,1);
    glScalef(0.15,0.15,0.15);
    ruleta2.draw(modo,r,g,b, grosor);
    glPopMatrix();

    // boton apagado
    glPushMatrix();
    glTranslatef(0,3.3,1.475);
    glRotatef(270,1,0,0);
    glScalef(0.05,0.05,0.05);
    boton_apagado.draw(modo, color_r_boton, 0, 0, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.7, -3.2, -1.7);
    glRotatef(giro_ruedas,0,1,0);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.7, -3.2, 1.7);
    glRotatef(giro_ruedas,0,1,0);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-3.2, -1.7);
    glRotatef(giro_ruedas,0,1,0);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,-3.2,1.7);
    glRotatef(giro_ruedas,0,1,0);
    rueda.draw(modo, r, g, b, grosor);
    glPopMatrix();

  glPopMatrix();
}


