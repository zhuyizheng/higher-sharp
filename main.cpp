#include <iostream>
#include <list>
#include <memory>
#include <chrono>
#include <vector>
#include <string>
#include <tuple>

#include <iterator>
#include <algorithm>

typedef std::chrono::high_resolution_clock Clock;

#include "sharp.h"



int main()
{
//TreeNode<unsigned long> a;
//cout<<"TreeNode long int size: "<<sizeof(a)<<endl;
//Tree<unsigned long> b;
//cout<<"Tree long int size: "<<sizeof(b)<<endl;
//TreeNode< pair<unsigned long, vector<unsigned long>>> c;
//cout<<"TreeNode pair of long int size: "<<sizeof(a)<<endl;
//cout<<String<unsigned long, vector<unsigned long>> (c );
//FuncTreeNode<TreeNode<TreeNode<int>>, string> d;
//cout<<"test size"<<sizeof(d)<<endl;

    Level_leq_2_Tree X;
    X.Input("X");
    Level_leq_2_Tree T (X);
  //  T.Input("T");
    Level_leq_2_Tree Q (X);
 //   Q.Input("Q");
 //   LevelOneTree W;
 //   W.Input("W");


    cout<<"starting computing tensor product"<<endl;
    auto t1 = Clock::now();

    unsigned long i = 0;

 /*   shared_ptr<Level_21_Desc> D = make_shared<Level_21_Desc> (Level_21_Desc());

    while (D!= nullptr)
    {
        ++i;
     //   cout<<D->String()<<endl;
                D = BKLeft(D, T, Q);

    }*/
    cout<<"*************"<<endl;

    auto sigma2 = TensorProduct(X,TensorProduct(T,Q).Domain());


    cout<<"number of desc: "<<sigma2.Cardinality()<<endl;
   // cout<<"number of desc: "<<i<<endl;


    auto t2 = Clock::now();
    long double mytime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()/double(1000000000);


    std::cout << "It took "
              << mytime
              << " seconds" << std::endl;



    cout<<"starting computing tensor product"<<endl;
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
