#include "grman/grman.h"
#include <iostream>
#include <map>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.construct_food_chain();
    g.afficherMap();
    g.supprimerSommet();
    g.test_remove_arete(4);
    g.afficherMap();
   // g.supprimerSommet();



    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )

    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

//        if (mouse_b&1 || mouse_b&2)
//        {

            //  printf("les coord de la souris sont x:%d y:%d\n", mouse_x, mouse_y);

//            couleur = getpixel(buffer2,mouse_x,mouse_y);
//
//            if (couleur == JAUNE)
//               //
//            if (couleur == ORANGE)
//                //
//            if (couleur == ROUGE)
//                //
//            if(couleur==VIOLETFONCE)
//                //
//            if(couleur==VIOLETCLAIR)
//                   //
//            if (couleur==ROSE)
//                //
//            if(couleur==NOIR)
//                return (0);
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


