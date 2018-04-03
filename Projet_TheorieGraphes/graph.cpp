#include "graph.h"

/***************************************************
                    Sommet
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
SommetInterface::SommetInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
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


/// Gestion du Sommet avant l'appel � l'interface
void Sommet::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Sommet apr�s l'appel � l'interface
void Sommet::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    Arete
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface

AreteInterface::AreteInterface(Vertex& from, Vertex& to)

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

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_Arete.add_child(m_box_Arete);
    m_box_Arete.set_dim(24,60);
    m_box_Arete.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_Arete.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_Arete.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Arete avant l'appel � l'interface
void Arete::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Arete apr�s l'appel � l'interface
void Arete::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent �tre d�finis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_Sommet(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_Sommet(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_Sommet(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_Sommet(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_Sommet(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_Sommet(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_Sommet(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_Sommet(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent �tre d�finis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_Arete(0, 1, 2, 50.0);
    add_interfaced_Arete(1, 0, 1, 50.0);
    add_interfaced_Arete(2, 1, 3, 75.0);
    add_interfaced_Arete(3, 4, 1, 25.0);
    add_interfaced_Arete(4, 6, 3, 25.0);
    add_interfaced_Arete(5, 7, 3, 25.0);
    add_interfaced_Arete(6, 3, 4, 0.0);
    add_interfaced_Arete(7, 2, 0, 100.0);
    add_interfaced_Arete(8, 5, 2, 20.0);
    add_interfaced_Arete(9, 3, 7, 80.0);
}

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_Aretes)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_Aretes)
        elt.second.post_update();

}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_Sommet(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding Sommet at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Sommet";
    }
    // Cr�ation d'une interface de sommet
    SommetInterface *vi = new SommetInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Sommet(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
void Graph::add_interfaced_Arete(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_Aretes.find(idx)!=m_Aretes.end() )
    {
        std::cerr << "Error adding Arete at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Arete";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding Arete idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding Arete";
    }

    AreteInterface *ei = new AreteInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_Arete);
    m_Aretes[idx] = Arete(weight, ei);
}

