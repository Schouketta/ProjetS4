#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "grman/grman.h"

/***************************************************
                    Sommet
****************************************************/

class SommetInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Sommet;
    friend class AreteInterface;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        // Une image de "remplissage"
        grman::WidgetImage m_img;

        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label précédent
        grman::WidgetText m_box_label_idx;

    public :

        // Le constructeur met en place les éléments de l'interface (voir l'implémentation dans le .cpp)
        SommetInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Sommet
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graph;
    friend class SommetInterface;
    friend class Arete;
    friend class AreteInterface;

    private :

        int m_indice;
        bool m_actif1;
        double m_value;//nb population (santé)
        std::string m_nomSommet;//espece ou biomasse

        /// liste des indices des arcs arrivant au sommet : accès aux prédécesseurs
        std::vector<int> m_in;

        /// liste des indices des arcs partant du sommet : accès aux successeurs
        std::vector<int> m_out;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<SommetInterface> m_interface = nullptr;
        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne précédente est en gros équivalent à la ligne suivante :
        // SommetInterface * m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface

        Sommet (int indice=0, std::string nomSommet="", double value=0, SommetInterface *interface=nullptr)
            : m_indice(indice), m_nomSommet(nomSommet),m_value(value), m_interface(interface)  { m_actif1=true; }

        /// Sommet étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Sommet (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
        void pre_update();
        void post_update();


        ///Ajout
        int augmenterN(int nb);
        int diminuerN(int nb);
        int formuleN();

        ///Getters & Setters

        int getIndice();
        void setIndice(int n);

        bool getActif1();
        void setActif1(bool a);

        double getValue();
        void getValue(double v);

        std::string getNomSommet();
        void setNomSommet(std::string n);


        std::vector<int> getm_in();
        std::vector<int> getm_out();
};



#endif // SOMMET_H_INCLUDED
