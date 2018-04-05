#include "Arete.h"
/***************************************************
                    Arete
****************************************************/

/// Le constructeur met en place les éléments de l'interface
AreteInterface::AreteInterface(Sommet& from, Sommet& to)
{
    // Le WidgetArete de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating AreteInterface between vertices having no interface" << std::endl;
        throw "Bad AreteInterface instanciation";
    }
    m_top_Arete.attach_from(from.m_interface->m_top_box);
    m_top_Arete.attach_to(to.m_interface->m_top_box);
    m_top_Arete.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_Arete.add_child(m_box_Arete);
    m_box_Arete.set_dim(24,60);
    m_box_Arete.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_Arete.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_Arete.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Arete avant l'appel à l'interface
void Arete::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Arete après l'appel à l'interface
void Arete::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}

int Arete::getIndice(int idx)
{
    return m_indiceArete;
}

void Arete::setIndice(int idx)
{
    m_indiceArete=idx;
}

double Arete::getWeight()
{
    return m_weight;
}
void Arete::setWeight(double w)
{
    m_weight=w;
}

int Arete::getActif()
{
    return m_actif;
}
void Arete::setActif(bool a)
{
    m_actif=a;
}

int Arete::getFrom()
{
    return m_from;
}
void Arete::setFrom(int depart)
{
    m_from=depart;
}

int Arete::getTo()
{
    return m_to;
}
void Arete::getTo(int arrivee)
{
    m_to=arrivee;
}

