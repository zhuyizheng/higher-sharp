#include <iostream>
#include <list>
#include <memory>
#include <chrono>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>

#include <iterator>
#include <algorithm>

typedef std::chrono::high_resolution_clock Clock;

#include "sharp.h"

#include "latex.h"



int main()
{

    ofstream myfile;
    myfile.open ("example.txt");
    
    while (true)
    {
        int choice;
        cout << "What do you want to compute? 0 to quit" << endl;
        cout << "1. Tensor product of (<=2, <=2) trees." << endl;
        cout << "2. Tensor product of (3, <=2) trees." << endl;
        cout << "3. Tensor product of (<=2, <=2, <=2) trees." << endl;
        cout << "4. Tensor product of (3, <=2, <=2) trees." << endl;
        cin >> choice;
        if (choice == 0)
        {
            return 0;
        }
        
// compute TQ tensor product
        if (choice == 1)
        {
            Level_leq_2_Tree X;
            X.Input ("T");
            
            
            Level_leq_2_Tree T ;
            T.Input ("Q");
            auto && U = TensorProduct (X, T);
            
            cout << endl << "The tensor product of T and Q is U." << endl;
            
            cout << "Level-1 component of U cardinality: "
                 << U.factor_1.Cardinality() - 1
                 << endl;
            cout << "Level-2 component of U cardinality: "
                 << U.factor_2.Cardinality()
                 << endl;
                 
            auto && c = Count (U.domain.tree_2);
            cout << "Level_2 component of U depth:"
                 << c.size() << endl;
            cout << "Node count each level | Node count with deg 1 each level" << endl;
            for (auto && i : c)
            {
                cout << i.first << "\t|\t" << i.second << endl;
            }
            
            cout << endl << "Generate LaTeX code? (Y/N) ";
            
            char x;
            cin >> x;
            if (x == 'y' || x == 'Y')
            {
                cout << latexpre;
                
                cout << Latex (U,
                               "U",
                               "\\alpha",
                               "g",
                               "\\item");
                cout << endl << "Finish!" << endl << endl;
            }
        }
        
//
        else if (choice == 2)
        {
            LevelThreeTree Y;
            Y.Input ("Y");
            
            
            Level_leq_2_Tree T ;
            T.Input ("T");
            auto && U = TensorProduct (Y, T);
            
            cout << endl << "The tensor product of Y and T is U." << endl;
            cout << "U cardinality: "
                 << U.Cardinality() - 1
                 << endl;
                 
                 
            cout << endl << "Generate LaTeX code? (Y/N)" << endl;
            
            char x;
            cin >> x;
            if (x == 'y' || x == 'Y')
            {
                cout << latexpre;
                
                cout << Latex (U,
                               "U",
                               "\\alpha",
                               "g",
                               "h",
                               "\\item");
                               
                cout << endl << "Finish!" << endl << endl;
            }
            
        }
        
        else if (choice == 3)
        {
            Level_leq_2_Tree X;
            X.Input ("X");
            Level_leq_2_Tree T;
            T.Input ("T");
            Level_leq_2_Tree Q;
            Q.Input ("Q");
            cout << TensorProduct (TensorProduct (X, T).domain, Q).Cardinality() << endl;
            cout << endl << "Generate LaTeX code? (Y/N) ";
            
            char x;
            cin >> x;
            if (x == 'y' || x == 'Y')
            {
                cout << latexpre;
                cout << LatexTensorProduct (X, T, Q) << endl;
                
            }
        }
        
        else if (choice == 4)
        {
            LevelThreeTree X;
            X.Input ("Y");
            Level_leq_2_Tree T;
            T.Input ("T");
            Level_leq_2_Tree Q;
            Q.Input ("Q");
            cout << TensorProduct (TensorProduct (X, T).domain, Q).Cardinality() << endl;
            cout << endl << "Generate LaTeX code? (Y/N) ";
            
            char x;
            cin >> x;
            if (x == 'y' || x == 'Y')
            {
                cout << latexpre;
                
                cout << LatexTensorProduct (X, T, Q) << endl;
                
            }
        }
    }
    
    
    cout << "starting computing tensor product" << endl;
    auto t1 = Clock::now();
    
    unsigned long i = 0;
    
    
//   auto && sigma7 = TensorProduct(X,TensorProduct(T,Q).domain).Cardinality()-1;

//   auto && sigma8 = TensorProduct(TensorProduct(T,Q).domain, X).Cardinality()-1;

//   cout<<sigma7<<endl<<sigma8<<endl;



// myfile<<endl<<"This tree has cardinality "<<sigma2<<".";


    myfile.close();
    
//  auto sigma2 = DynamicTensorProduct(X,TensorProduct(T,Q).domain, myfile);
//  auto sigma2 = DynamicTensorProduct(X,T, myfile);


// auto && sigma2 = TensorProduct(TensorProduct(Y,T).domain,Q);
//   cout<<endl<<"number of desc: "<<sigma2.Cardinality()<<endl;

//auto && sigma3 = TensorProduct(Y,TensorProduct(T,Q).domain);

    auto t2 = Clock::now();
    long double mytime = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1).count() / double (1000000000);
    
    
    std::cout << "It took "
              << mytime
              << " seconds" << std::endl;
//                 cout<<endl<<"number of desc: "<<sigma3.Cardinality()<<endl;

//
//cout<<"showing latex:"<<endl;
//int gang;
//cin>>gang;
//cout<<Latex(sigma2,
//            "R",
//             "\\beta",
//             "\\alpha",
//             "\\item")<<endl;


//  auto sigma3 = DynamicTensorProduct(TensorProduct(T,Q).domain, X, myfile);
    //  auto sigma2 = TensorProduct(T,Q).Cardinality()-1;
    
    
//   cout<<endl<<"number of desc: "<<sigma2.Cardinality()<<endl;
//   cout<<endl<<"number of desc: "<<sigma3.Cardinality()<<endl;




//   cout<<"starting computing tensor product"<<endl;
    /*   auto t3 = Clock::now();
    
    
       shared_ptr<Level_21_Desc> D = make_shared<Level_21_Desc> (Level_21_Desc());
    
       while (D!= nullptr)
       {
           ++i;
        //   cout<<D->String()<<endl;
                   D = BKLeft(D, T, Q);
    
       }*/
    /*
    cout<<"*************"<<endl;
    
    auto sigma3 = TensorProduct(TensorProduct(T,T).domain,T);
    
    
    cout<<"number of desc: "<<sigma3.Cardinality()<<endl
    // cout<<"number of desc: "<<i<<endl;
    
    
    auto t4 = Clock::now();
    mytime = std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count()/double(1000000000);
    
    
    
    std::cout << "It took "
              << mytime
              << " seconds" << std::endl;*/
    
    
//P.Show();

    /*
    LevelOneTree P;
    P.Input("P",3);
    
            cout<<"P card:"<<P.Cardinality()<<endl;
        LevelTwoTree Q;
        Q.Input("Q",2);
            cout<<"Q card:"<<Q.Cardinality()<<endl;
    
    
        cout << "Hello world!" << endl;
        return 0;*/
}
