#include "graph.h"
#include <fstream>
#include <iostream>

/***************************************************
                    GRAPH
****************************************************/

using namespace std;

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
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


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    //add_interfaced_Sommet(0, 30.0, 200, 100, "jellyfish.jpg");
//    add_interfaced_Sommet(1, 60.0, 400, 100, "clown2.jpg");
//    add_interfaced_Sommet(2,  50.0, 200, 300, "clown3.jpg");
//    add_interfaced_Sommet(3,  0.0, 400, 300, "clown4.jpg");
//    add_interfaced_Sommet(4,  100.0, 600, 300, "clown5.jpg");
//    add_interfaced_Sommet(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg",0);
//    add_interfaced_Sommet(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg",1);
//    add_interfaced_Sommet(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
//    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
//    add_interfaced_Arete(0, 1, 2, 50.0);
//    add_interfaced_Arete(1, 0, 1, 50.0);
//    add_interfaced_Arete(2, 1, 3, 75.0);
//    add_interfaced_Arete(3, 4, 1, 25.0);
//    add_interfaced_Arete(4, 6, 3, 25.0);
//    add_interfaced_Arete(5, 7, 3, 25.0);
//    add_interfaced_Arete(6, 3, 4, 0.0);
//    add_interfaced_Arete(7, 2, 0, 100.0);
//    add_interfaced_Arete(8, 5, 2, 20.0);
//    add_interfaced_Arete(9, 3, 7, 80.0);
}

void Graph::construct_food_chain()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    chargerGraphe();



}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
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

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_Sommet(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{

    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding Sommet at idx=" << idx << " already used..." << std::endl;
        throw "Error adding Sommet";
    }
    // Création d'une interface de sommet
    SommetInterface *vi = new SommetInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Sommet(idx, value, vi);
}

/// Aide à l'ajout d'arcs interfacés
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
    m_Aretes[idx].setIndice(idx);
    m_Aretes[idx].m_from=id_vert1;
    m_Aretes[idx].m_to=id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);


}

void Graph::chargerGraphe()
{
    std::ifstream fichier("graphetest.txt", ios::in);

    if(fichier)
    {

        fichier >> m_ordre; //on récupère l'ordre de la matrice
        fichier >> m_nbArete; //on récupère le nombre d'arpete du graphe

        int indice_sommet;
        double jauge;
        //bool actif1;
        int x;
        int y;
        std::string image;
        // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
        int indice_arc;
        int sommet_depart;
        int sommet_arrivee;
        double poids;

        cout<<"ordre : "<<m_ordre<<endl;
        cout<<"nb Aretes : "<<m_nbArete<<endl;

        for(int i=0; i<m_ordre; i++) //Pour remplir le tableau de Sommets (nom des individus) avec le fichier
        {
            fichier >> indice_sommet>>jauge>>x>>y>>image;


            cout<<"indice sommet : "<<indice_sommet<<endl;
            cout<<"jauge : "<<jauge<<endl;
            cout<<"x et y: "<<x<<" et "<<y<<endl;
            cout<<"nom image : "<<image<<endl;


            add_interfaced_Sommet(indice_sommet, jauge, x, y, image);
            //cout<<"apres add interface sommet"<<endl;


        }

        for(int i=0; i<m_nbArete; i++)
        {
            fichier>>indice_arc>>sommet_depart>>sommet_arrivee>>poids;

            add_interfaced_Arete(indice_arc, sommet_depart, sommet_arrivee, poids);

        }


        cout<<endl;

        fichier.close();

    }
    else if(!fichier)
    {
        cout<<"PB D'OUVERTURE DU FICHIER"<<endl;
    }
}

void Graph::sauvegarderGraphe()
{

}

void Graph::ajouterSommet()
{

}

void Graph::supprimerSommet()
{
    int choix=0;
    cout<<"Quelle espece voulez-vous supprimer ? (Taper le n° de l'espece associe)"<<endl;
    cin>>choix;


    std::map<int,Sommet> ::iterator it;
    //std::vector<int>::iterator it1;

    auto it2 = m_vertices.find(choix);

    for (int i=0; i<(*it2).second.getm_out().size(); i++)
    {
        cout<<"test"<<it2->second.getm_out()[i];
    }

    for (int i=0; i<(*it2).second.getm_in().size(); i++)
    {
        test_remove_arete (it2->second.getm_in()[i]) ;
    }

    for (int i=0; i<(*it2).second.getm_out().size(); i++)
    {
        test_remove_arete (it2->second.getm_out()[i]) ;
    }

//    for(it=m_vertices.begin(); it!=m_vertices.end(); it++)
//    {
//        if(it->first == choix)
//        {
//            for(it1=(*it).second.getm_in().size(); it1!=it->second.getm_in().end(); it1++)
//            {
//
//            }
//        }
//    }






}

void Graph::afficherGraphe()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    std::map<int,Arete> ::iterator it5;

    std::map<int,Sommet> ::iterator it;

    for(it=m_vertices.begin(); it !=m_vertices.end(); it++)
    {

        //add_interfaced_Sommet(it->first, it->second.m_value, it->second.m_interface.x,  it->second.y, it->second.)
    }

    cout<<"dfhefuufeeu";


    for(it5=m_Aretes.begin(); it5 !=m_Aretes.end(); it5++)
    {
        cout<<"avant"<<endl;
        cout<<it5->first;
        add_interfaced_Arete(it5->first,it5->second.m_from, it5->second.m_to, it5->second.m_weight);

        cout<<"apres for"<<endl;
    }

//            for(int i=0; i<m_ordre; i++) //Pour remplir le tableau de Sommets (nom des individus) avec le fichier
//        {
//
//            add_interfaced_Sommet(indice_sommet, jauge, x, y, image);
//
//
//
//        }
//
//        for(int i=0; i<m_nbArete; i++)
//        {
//            fichier>>indice_arc>>sommet_depart>>sommet_arrivee>>poids;
//
//            add_interfaced_Arete(indice_arc, sommet_depart, sommet_arrivee, poids);
//
//        }
}

void Graph::afficherMap()
{
    std::map<int,Sommet> ::iterator it;

    for(it=m_vertices.begin(); it !=m_vertices.end(); it++)
    {
        cout<< "Indice du sommet : "<<it->first<< " | population : ";
        cout<<it->second.m_value<<std::endl;
    }

//    auto it2 = m_vertices.find(2);
//
//    if (it2!=m_vertices.end())
//    {
//        cout <<it2->second.m_value<<endl;
//
//    }


    std::map<int,Arete> ::iterator it1;
    for(it1=m_Aretes.begin(); it1 !=m_Aretes.end(); it1++)
    {
        cout<< "Indice de l'arete : "<<it1->first<< " | poids arete : ";
        cout<<it1->second.m_weight<<std::endl;
    }
}

void Graph::test_remove_arete(int eidx)
{
    /// référence vers le Arete à enlever

    Arete &remed=m_Aretes.at(eidx);

    std::cout << "Removing arete " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2

    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;

    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;

    std::cout << m_Aretes.size() << std::endl;



    /// test : on a bien des éléments interfacés

    if (m_interface && remed.m_interface)

    {

        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :

        /* AreteInterface *ei = new AreteInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */

        /* m_interface->m_main_box.add_child(ei->m_top_Arete);  */

        /* m_Aretes[idx] = Arete(weight, ei); */

        /// Le new AreteInterface ne nécessite pas de delete car on a un shared_ptr

        /// Le Arete ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)

        /// mais il faut bien enlever le conteneur d'interface m_top_Arete de l'arc de la main_box du graphe

        m_interface->m_main_box.remove_child( remed.m_interface->m_top_Arete );

    }



    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !

    /// References sur les listes de Aretes des sommets from et to

    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;

    std::vector<int> &veto = m_vertices[remed.m_to].m_in;

    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );

    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );



    /// Le Arete ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)

    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Arete et le AreteInterface

    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_Arete en tant que child de main_box !

    m_Aretes.erase( eidx );





    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2

    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;

    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;

    std::cout << m_Aretes.size() << std::endl;



}


std::map<int,Sommet> Graph::getMapSommet()
{
    return m_vertices;
}

std::map<int,Arete> Graph::getMapArete()
{
    return m_Aretes;
}
