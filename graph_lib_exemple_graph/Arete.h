#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "grman/grman.h"
#include "Sommet.h"

/***************************************************
                    Arete
****************************************************/

class AreteInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Arete;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // Le WidgetArete qui "contient" toute l'interface d'un arc
        grman::WidgetArete m_top_Arete;

        // Une boite pour englober les widgets de réglage associés
        grman::WidgetBox m_box_Arete;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        AreteInterface(Sommet& from, Sommet& to);
};


class Arete
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graph;
    friend class AreteInterface;

    private :

        int m_indiceArete;
        bool m_actif;
        /// indice du sommet de départ de l'arc
        int m_from;



        /// indice du sommet d'arrivée de l'arc
        int m_to;

        /// un exemple de donnée associée à l'arc, on peut en ajouter d'autres...
        double m_weight;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<AreteInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Arete (double weight=0, AreteInterface *interface=nullptr) :
           m_weight(weight), m_interface(interface)  { m_actif=true; }

        /// Arete étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Arete (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
        void setIndice(int idx);
        void pre_update();
        void post_update();
};


#endif // ARETE_H_INCLUDED
