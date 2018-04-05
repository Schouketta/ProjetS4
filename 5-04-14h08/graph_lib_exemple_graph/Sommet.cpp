#include "Sommet.h"
/***************************************************
                    Sommet
****************************************************/
using namespace std;
//Sommet::Sommet ()
//            : m_N(0), m_nomSommet(""),m_actif(true),m_x(0), m_y(0), m_value(0) //m_interface(interface)
//{
//
//}

//Sommet::Sommet (int N, std::string nomSommet, bool actif, int x, int y, double value, SommetInterface *interface=nullptr)
//            : m_N(N), m_nomSommet(nomSommet),m_actif(true),m_x(x), m_y(y), m_value(value), m_interface(interface)
//{
//
//}

/// Le constructeur met en place les éléments de l'interface
SommetInterface::SommetInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}



int Sommet::augmenterN(int nb)
{
    this->m_value=(this->m_value)+ nb;
    return m_value;
}

int Sommet::diminuerN(int nb)
{
    std::cout<<"Attention! Diminution de la population : "<<std::endl;
    cout<<"La population passe de "<<m_value;
    this->m_value = this->m_value - nb;

    if (m_value < 0) //Eviter d'avoir une vie négative
    {
        m_value = 0; //Perso KO
    }

    std::cout<<" à "<<m_value<<endl;
    return m_value;
}

int Sommet::formuleN()
{
    //m_value=
    return m_value;
}

/// Gestion du Sommet avant l'appel à l'interface
void Sommet::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Sommet après l'appel à l'interface
void Sommet::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}

int Sommet::getIndice()
{
    return m_indice;
}

void Sommet::setIndice(int n)
{
    m_indice = n;
}

double Sommet::getValue()
{
    return m_value;
}

void Sommet::getValue(double v)
{
    m_value=v;
}

std::vector<int> Sommet::getm_in()
{
    return m_in;
}

std::vector<int> Sommet::getm_out()
{
    return m_out;
}

bool Sommet::getActif1()
{
    return m_actif1;
}

void Sommet::setActif1(bool a)
{
    m_actif1=a;
}

std::string Sommet::getNomSommet()
{
    return m_nomSommet;
}

void Sommet::setNomSommet(std::string n)
{
    m_nomSommet=n;
}
