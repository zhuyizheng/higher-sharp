#ifndef LATEX_H_INCLUDED
#define LATEX_H_INCLUDED

 string latexpre = "\\newcommand\\newcommand{\\comp}[2]{{}^{#1}\\!#2}\n\\newcommand{\\tree}{\\operatorname{tree}}\n\\newcommand{\\node}{\\operatorname{node}}\n";

string Latex (const DEGREE & d)
{
    if (d == DEGREE::ZERO)
    {
        return to_string (0);
    }
    else if (d == DEGREE::ONE)
    {
        return to_string (1);
    }
    else
    {
        return to_string (2);
    }
}
string Latex (const SingleSequence & s)
{

    if (s.empty() )
    {
        return "\\emptyset";
    }
    string output = "(";
    for (auto && i : s)
    {
        output += to_string (i) + ", ";
    }
    output.pop_back();
    output.pop_back();
    output += ")";
    return output;
}

string Latex (const DoubleSequence & s)
{

    if (s.empty() )
    {
        return "\\emptyset";
    }
    string output = "(";
    for (auto && i : s)
    {
        output += Latex (i) + ", ";
    }
    output.pop_back();
    output.pop_back();
    output += ")";
    return output;
}

string Latex (const leq_2_Sequence & s)
{
    if (std::get<0> (s) == DEGREE::ZERO)
    {
        return "(0, -1)";
    }
    else if (std::get<0> (s) == DEGREE::ONE)
    {
        string output;
        output  +=  "(1, ";
        
        output += Latex (std::get<1> (s) );
        
        output +=  ")";
        return output;
    }
    else
    {
        string output;
        output  +=  "(2, ";
        
        output += Latex (std::get<2> (s) );
        
        output +=  ")";
        return output;
    }
    
}

string Latex (const LevelOneTree & P)
{
    if (P.IsTrivial() )
    {
        return "\\emptyset";
    }
    string output;
    output += "\\{";
    for (auto && i = P.SmallestNode();
            i != P.Root();
            i = P.NextEnumerate (i) )
    {
        output += Latex (P.EntireEntry (i) );
        output += ",";
    }
    output.pop_back();
    output.pop_back();
    output += "\\}";
    return output;
}

string Latex (const Level_21_Desc & D,
              const string & symbol_of_ordinal)
{
    string output;
    if (D.Degree() == DEGREE::ONE)
    {
        output += "(1, (";
        output += Latex (D.sequence_1);
        output += "))";
    }
    else
    {
        if (D.IsConstant() )
        {
            return "(2, $\\emptyset$)";
        }
        output += "(2, (";
        for (auto && i = 0;
                i < D.sequence_2.size();
                ++ i)
        {
            output += "$";
            output += symbol_of_ordinal;
            output += "_{";
            output += Latex ( ( (D.enumeration) [i + 1])->LastEntry().second);
            output += "}$, ";
            output += Latex (D.sequence_2[i]);
            output += ", ";
        }
        
        if (D.IsContinuousTypeAtDomain() )
        {
            output += "$";
            
            output += symbol_of_ordinal;
            output += "_{";
            
            output += Latex (D.enumeration.back()->LastEntry().second);
            output += "}$, $-1$";
        }
        else
        {
            output.pop_back();
            output.pop_back();
        }
        output += "))";
    }
    return output;
}

string Latex_for_332 (const Level_21_Desc & D,
              const string & symbol_of_function)
{
    string output;
    if (D.Degree() == DEGREE::ONE)
    {
        output += "(1, (";
        output += Latex (D.sequence_1);
        output += "))";
    }
    else
    {
        if (D.IsConstant() )
        {
            return "(2, $\\emptyset$)";
        }
        output += "(2, (";
        for (auto && i = 0;
                i < D.sequence_2.size();
                ++ i)
        {
            output += "$";
            output += symbol_of_function;
            output += "$";
            output += "(1, ";
            output += Latex ( ( (D.enumeration) [i + 1])->LastEntry().second);
            output += "), ";
            output += Latex (D.sequence_2[i]);
            output += ", ";
        }
        
        if (D.IsContinuousTypeAtDomain() )
        {
            output += "$";
            
            output += symbol_of_function;
             output += "$";
           output += "(1, ";
            output += Latex ( ( (D.enumeration.back()))->LastEntry().second);
            output += "), ";
            output += "$, $-1$";
        }
        else
        {
            output.pop_back();
            output.pop_back();
        }
        output += "))";
    }
    return output;
}



string Latex (const Level_221_Desc & D,
              const string & symbol_of_ordinal,
              const string & symbol_of_function)
{
    string output;
    if (D.Degree() == DEGREE::ONE)
    {
        output += "(1, ( ";
        output += Latex (D.sequence_1);
        output += "))";
    }
    else
    {
        if (D.IsConstant() )
        {
            return "(2, $\\emptyset$)";
        }
        output += "(2, (";
        for (auto && i = 0;
                i < D.sequence_2.size();
                ++ i)
        {
            output += "$";
            output += symbol_of_function;
            output += "$";
            output += Latex ( (D.enumeration) [i + 1]->LastEntry().second,
                              symbol_of_ordinal);
            
            output += ", ";
            output += Latex (D.sequence_2[i]);
            output += ", ";
        }
        
        if (D.IsContinuousTypeAtDomain() )
        {
             output += "$";
           output += symbol_of_function;
            output += "$";
            output += Latex ( D.enumeration.back()->LastEntry().second,
                              symbol_of_ordinal);
            output += ", $-1$";
        }
        else
        {
            output.pop_back();
            output.pop_back();
        }
        output += "))";
    }
    return output;
}


string Latex (const Level_222_Factor & rho,
              const string & tree_name,
              const string & symbol_of_ordinal,
              const string & symbol_of_function,
              const string & enumword)
{
    
 
    string output;
    {
        auto i = rho.domain.tree_2.Root()->BKLeft();
        auto j = rho.factor_2.Root()->BKLeft();
        while (i != nullptr)
        {
         
            output += enumword ;
            output += " ";
             
             
            output += "$\\comp{2}{";
            output += tree_name;
            output += "}_{\\node}(";
            output += Latex (rho.domain.tree_2.EntireEntryInDomain (i) );
            output += ")";
            output += "= ";
             
            if (rho.domain.tree_2.Degree(i) == DEGREE::ZERO)
            {
                output += "-1";
            }
            else{
            output += Latex (rho.domain.tree_2.Value (i).CreateHangingSequence() );
            }
             
            output += "$";
             
            output += "\n\n";
             
            output += Latex (j->LastEntry().second,
                             symbol_of_ordinal,
                             symbol_of_function);
            output += "\n\n";
            i = i->BKLeft();
            j = j->BKLeft();
        }
    }
    {
        auto i = rho.domain.tree_1.Root()->BKLeft();
        auto j = rho.factor_1.Root()->BKLeft();
        while (i != nullptr)
        {
         
            output += enumword ;
            output += " ";
             
             
            output += "";
            output += "$\\comp{1}{";
            output += tree_name;
            output += "}$ contains ";
            output += Latex (rho.domain.tree_1.EntireEntry (i) );

            output += "\n\n";
             
            output += Latex (j->LastEntry().second,
                             symbol_of_ordinal);
            output += "\n\n";
            i = i->BKLeft();
            j = j->BKLeft();
        }
    }
    return output;
}


string Latex (const Level_322_Desc & D,
              const string & symbol_of_ordinal,
              const string & symbol_of_function,
              const string & symbol_of_outside_function
             )
{
    string output;

    output += "( ";
    output += Latex (D.sequence.front() );
    output += ", ";

    for (auto && i = 1;
            i < D.sequence.size();
            ++ i)
    {

        if (Degree ( (D.enumeration) [i]) == DEGREE::ONE)
        {
            output += "$";
            output += symbol_of_outside_function;
            output += "$";
            
            output += Latex_for_332(D.factor.Value_1 (D.enumeration[i]),
                             symbol_of_function);
            output += "$";
        }
        else
        {
            output += "$[ \\vec{";
            output += symbol_of_ordinal;
            output += "} \\mapsto ";
            
            output += symbol_of_outside_function;
            output += "$";
            output += Latex (D.factor.Value_2 (D.enumeration[i]),
                             symbol_of_ordinal,
                             symbol_of_function);
            output += "$]_{\\mu_{\\vec{";
            output += symbol_of_ordinal;
            output += "}}}$";
        }


        output += ", ";
        output += "";
        output += Latex (D.sequence[i]);
        output += "";
        output += ", ";
    }
    if (D.IsContinuousTypeAtDomain() )
    {


        if (Degree ( (D.enumeration).back() ) == DEGREE::ONE)
        {

            output += "$";
            output += symbol_of_outside_function;
            output += "$";
            output += Latex_for_332 (D.factor.Value_1 (D.enumeration.back()),
                             symbol_of_function);
        }
        else
        {
            
            output += "$[ \\vec{";
            output += symbol_of_ordinal;
            output += "} \\mapsto ";
            
            output += symbol_of_outside_function;
            output += "$";
            output += Latex (D.factor.Value_2 (D.enumeration.back()),
                             symbol_of_ordinal,
                             symbol_of_function);
                             
            output += "$]_{\\mu_{\\vec{";
            output += symbol_of_ordinal;
            output += "}}}$";
        }
        output += ", $-1$";
    }
    else
    {
        output.pop_back();
        output.pop_back();
    }

    output += " )";
    return output;
}

string Latex (const Level_332_Factor & rho,
              const string & lv_3_tree_name,
              const string & symbol_of_ordinal,
              const string & symbol_of_function,
              const string & symbol_of_outside_function,
              const string & enumword)
{

    string output;
    auto i = rho.domain.Root()->BKLeft();
    auto j = rho.factor.Root()->BKLeft();
    while (i != nullptr)
    {

        output += enumword ;
        output += " ";



        if (i->Length() == 1){
            output += "$";
            output += lv_3_tree_name;
            output += "(";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += ")";
            output += "$ ";
            output += " has degree ";
            output += Latex(rho.domain.Degree(i));
        }
        else{

            output += "$";
            output += lv_3_tree_name;
            output += "_{\\tree}(";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += ")";
            output += "=$ ";

            output += "";

            if (rho.domain.Degree(i->Parent()) == DEGREE::ONE){
                output += "the unique completion of $";
                output += lv_3_tree_name;
                output += "(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")$";
            }
            else{
                output += "the completion of $";
                output += lv_3_tree_name;
                output += "(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")$";
                output += " that sends $";

                auto && critical_leq_2_tree_parent = rho.domain.Value(i->Parent());

                auto hanging_sequence = critical_leq_2_tree_parent.CreateHangingSequence();

                auto hanging_minus = hanging_sequence;
                if (std::get<0>(hanging_minus) == DEGREE::ONE){
                        std::get<1>(hanging_minus).pop_back();}
                else{
                        std::get<2>(hanging_minus).pop_back();}

                output += Latex(hanging_sequence);
                output += "$ to the completion of $";
                output += lv_3_tree_name;
                output += "_{\\tree}(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")";
                output += "";
                output += Latex(hanging_minus);
                output += "$ ";
                output += " whose node component is $";



                auto && Ww = rho.domain.Partial(i);
                auto && w = Ww.NodeMinusInTree();
                if (w == nullptr){
                    output += "-1$";
                }
                else{
                    output += Latex(Ww.CreateHangingSequence());
                    output += "$";
                }
            }

            output += "\n\n\\noindent";

            output += "$";
            output += lv_3_tree_name;
            output += "_{\\node}";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += "";
            output += "= ";

            output += Latex(rho.domain.Value(i).CreateHangingSequence());

            output += "$";
        }


        output += "\n\n";

        output += Latex (j->LastEntry().second,
                         symbol_of_ordinal,
                         symbol_of_function,
                         symbol_of_outside_function);
        output += "\n\n";
        i = i->BKLeft();
        j = j->BKLeft();
    }
    return output;
}


string LatexRep (const Level_21_Desc & D)

{
    string output;
    if (D.Degree() == DEGREE::ONE)
    {
        output += "(1, (";
        output += Latex (D.sequence_1);
        output += "))";
    }
    else
    {
        if (D.IsConstant() )
        {
            return "(2, $\\emptyset$)";
        }
        output += "(2, (";
        for (auto && i = 0;
                i < D.sequence_2.size();
                ++ i)
        {
            output += "";
            output += Latex ( ( (D.enumeration) [i + 1])->LastEntry().second);
            output += ", ";
            output += Latex (D.sequence_2[i]);
            output += ", ";
        }
        
        if (D.IsContinuousTypeAtDomain() )
        {
            
            output += Latex (D.enumeration.back()->LastEntry().second);
            output += ", $-1$";
        }
        else
        {
            output.pop_back();
            output.pop_back();
        }
        output += "))";
    }
    return output;
}

string LatexRep (const Level_221_Desc & D)
{
    
    string output;
    if (D.Degree() == DEGREE::ONE)
    {
        output += "(1, ( ";
        output += Latex (D.sequence_1);
        output += "))";
    }
    else
    {
        if (D.IsConstant() )
        {
            return "(2, $\\emptyset$)";
        }
        output += "(2, (";
        for (auto && i = 0;
                i < D.sequence_2.size();
                ++ i)
        {
            output += LatexRep ( (D.enumeration) [i + 1]->LastEntry().second);
            
            output += ", ";
            output += Latex (D.sequence_2[i]);
            output += ", ";
        }
        
        if (D.IsContinuousTypeAtDomain() )
        {
            output += LatexRep ( D.enumeration.back()->LastEntry().second);
            output += ", $-1$";
        }
        else
        {
            output.pop_back();
            output.pop_back();
        }
        output += "))";
    }
    return output;
}

string LatexRep (const Level_322_Desc & D){
    string output;

    output += "( ";
    output += Latex (D.sequence.front() );
    output += ", ";

    for (auto && i = 1;
            i < D.sequence.size();
            ++ i)
    {

        if (Degree ( (D.enumeration) [i]) == DEGREE::ONE)
        {
            
            output += LatexRep(D.factor.Value_1 (D.enumeration[i]));
        }
        else
        {
            output += LatexRep (D.factor.Value_2 (D.enumeration[i]));
        }


        output += ", ";
        output += "";
        output += Latex (D.sequence[i]);
        output += "";
        output += ", ";
    }
    if (D.IsContinuousTypeAtDomain() )
    {


        if (Degree ( (D.enumeration).back() ) == DEGREE::ONE)
        {

            output += LatexRep (D.factor.Value_1 (D.enumeration.back()));
        }
        else
        {
            output += LatexRep (D.factor.Value_2 (D.enumeration.back()));
        }
        output += ", $-1$";
    }
    else
    {
        output.pop_back();
        output.pop_back();
    }

    output += " )";
    return output;
}

string LatexRep (const Level_222_Factor & rho,
                 const string & tree_name,
                 const string & factor_name,
                 const string & enumword){
     
    string output;
    {
        auto i = rho.domain.tree_2.Root()->BKLeft();
        auto j = rho.factor_2.Root()->BKLeft();
        while (i != nullptr)
        {
         
            output += enumword ;
            output += " ";
             
             
            output += "$\\comp{2}{";
            output += tree_name;
            output += "}_{\\node}(";
            output += Latex (rho.domain.tree_2.EntireEntryInDomain (i) );
            output += ")";
            output += "= ";
             
            if (rho.domain.tree_2.Degree(i) == DEGREE::ZERO)
            {
                output += "-1";
            }
            else{
            output += Latex (rho.domain.tree_2.Value (i).CreateHangingSequence() );
            }
             
            output += "$";
             
            output += "\n\n";
             
             output += "$\\langle\\langle";
             output += factor_name;
            output += Latex (rho.domain.tree_2.EntireEntryInDomain (i) );            
             output += "\\rangle\\rangle";
            output += "=$";
            
            output += LatexRep (j->LastEntry().second);
            output += "\n\n";
            i = i->BKLeft();
            j = j->BKLeft();
        }
    }
    {
        auto i = rho.domain.tree_1.Root()->BKLeft();
        auto j = rho.factor_1.Root()->BKLeft();
        while (i != nullptr)
        {
         
            output += enumword ;
            output += " ";
             
             
            output += "$\\comp{1}{";
            output += tree_name;
            output += "}$ contains ";
            output += Latex (rho.domain.tree_1.EntireEntry (i) );
             
            output += "\n\n";
             
             output += "$\\langle\\langle";
             output += factor_name;
            output += Latex (rho.domain.tree_1.EntireEntry (i) );
             output += "\\rangle\\rangle";
            output += "=$";
            
            output += LatexRep (j->LastEntry().second);
            output += "\n\n";
            i = i->BKLeft();
            j = j->BKLeft();
        }
    }
    return output;

}

string LatexRepDual (const Level_222_Factor & rho,
                     const Level_222_Factor & rho_prime,
                 const string & tree_name,
                 const string & factor_name,
                 const string & factor_prime_name, 
                 const string & enumword){
                 
 
    string output;
    {
        auto i = rho.domain.tree_2.Root()->BKLeft();
        auto j = rho.factor_2.Root()->BKLeft();
        auto i_prime = rho_prime.domain.tree_2.Root()->BKLeft();
        auto j_prime = rho_prime.factor_2.Root()->BKLeft();
        while (i != nullptr)
        {
         
            output += enumword ;
            output += " ";
             
             
            output += "$\\comp{2}{";
            output += tree_name;
            output += "}_{\\node}(";
            output += Latex (rho.domain.tree_2.EntireEntryInDomain (i) );
            output += ")";
            output += "= ";
             
            if (rho.domain.tree_2.Degree(i) == DEGREE::ZERO)
            {
                output += "-1";
            }
            else{
            output += Latex (rho.domain.tree_2.Value (i).CreateHangingSequence() );
            }
             
            output += "$";
             
            output += "\n\n";
             
             output += "$\\langle\\langle";
             output += factor_name;
            output += Latex (rho.domain.tree_2.EntireEntryInDomain (i) );            
             output += "\\rangle\\rangle";
            output += "=$ ";
            
            output += LatexRep (j->LastEntry().second);
            output += "\n\n";
            
            
            i = i->BKLeft();
            j = j->BKLeft();
            
             output += "$\\langle\\langle";
             output += factor_prime_name;
            output += Latex (rho_prime.domain.tree_2.EntireEntryInDomain (i_prime) );            
             output += "\\rangle\\rangle";
            output += "=$ ";
            
            output += LatexRep (j_prime->LastEntry().second);
            output += "\n\n";
            
            
            i_prime = i_prime->BKLeft();
            j_prime = j_prime->BKLeft();
        }
    }
    {
        auto i = rho.domain.tree_1.Root()->BKLeft();
        auto j = rho.factor_1.Root()->BKLeft();
        auto i_prime = rho_prime.domain.tree_1.Root()->BKLeft();
        auto j_prime = rho_prime.factor_1.Root()->BKLeft();
        while (i != nullptr)
        {
         
            output += enumword ;
            output += " ";
             
             
            output += "$\\comp{1}{";
            output += tree_name;
            output += "}$ contains ";
            output += Latex (rho.domain.tree_1.EntireEntry (i) );
             
            output += "\n\n";
             
             output += "$\\langle\\langle";
             output += factor_name;
            output += Latex (rho.domain.tree_1.EntireEntry (i) );
             output += "\\rangle\\rangle";
            output += "=$ ";
            
            output += LatexRep (j->LastEntry().second);
            output += "\n\n";
            i = i->BKLeft();
            j = j->BKLeft();
            
             output += "$\\langle\\langle";
             output += factor_prime_name;
            output += Latex (rho_prime.domain.tree_1.EntireEntry (i_prime) );
             output += "\\rangle\\rangle";
            output += "=$ ";
            
            output += LatexRep (j_prime->LastEntry().second);
            output += "\n\n";
            i_prime = i_prime->BKLeft();
            j_prime = j_prime->BKLeft();
        }
    }
    return output;
}

string LatexRep (const Level_332_Factor & rho,
              const string & lv_3_tree_name,
              const string & factor_name,
              const string & enumword)
{

    string output;
    auto i = rho.domain.Root()->BKLeft();
    auto j = rho.factor.Root()->BKLeft();
    while (i != nullptr)
    {

        output += enumword ;
        output += " ";



        if (i->Length() == 1){
            output += "$";
            output += lv_3_tree_name;
            output += "(";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += ")";
            output += "$ ";
            output += " has degree ";
            output += Latex(rho.domain.Degree(i));
        }
        else{

            output += "$";
            output += lv_3_tree_name;
            output += "_{\\tree}(";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += ")";
            output += "=$ ";

            output += "";

            if (rho.domain.Degree(i->Parent()) == DEGREE::ONE){
                output += "the unique completion of $";
                output += lv_3_tree_name;
                output += "(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")$";
            }
            else{
                output += "the completion of $";
                output += lv_3_tree_name;
                output += "(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")$";
                output += " that sends $";

                auto && critical_leq_2_tree_parent = rho.domain.Value(i->Parent());

                auto hanging_sequence = critical_leq_2_tree_parent.CreateHangingSequence();

                auto hanging_minus = hanging_sequence;
                if (std::get<0>(hanging_minus) == DEGREE::ONE){
                        std::get<1>(hanging_minus).pop_back();}
                else{
                        std::get<2>(hanging_minus).pop_back();}

                output += Latex(hanging_sequence);
                output += "$ to the completion of $";
                output += lv_3_tree_name;
                output += "_{\\tree}(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")";
                output += "";
                output += Latex(hanging_minus);
                output += "$ ";
                output += " whose node component is $";



                auto && Ww = rho.domain.Partial(i);
                auto && w = Ww.NodeMinusInTree();
                if (w == nullptr){
                    output += "-1$";
                }
                else{
                    output += Latex(Ww.CreateHangingSequence());
                    output += "$";
                }
            }

            output += "\n\n\\noindent";

            output += "$";
            output += lv_3_tree_name;
            output += "_{\\node}";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += "";
            output += "= ";

            output += Latex(rho.domain.Value(i).CreateHangingSequence());

            output += "$";
        }


        output += "\n\n";

output += "$\\langle\\langle";
             output += factor_name;
            output += Latex (rho.domain.EntireEntryInDomain (i) );            
             output += "\\rangle\\rangle";
            output += "=$";
            
        output += LatexRep (j->LastEntry().second);
        output += "\n\n";
        i = i->BKLeft();
        j = j->BKLeft();
    }
    return output;
}
string LatexRepDual (const Level_332_Factor & rho,
                     const Level_332_Factor & rho_prime,
              const string & lv_3_tree_name,
              const string & factor_name,
              const string & factor_prime_name,
              const string & enumword)
{

    string output;
    auto i = rho.domain.Root()->BKLeft();
    auto j = rho.factor.Root()->BKLeft();
    auto i_prime = rho_prime.domain.Root()->BKLeft();
    auto j_prime = rho_prime.factor.Root()->BKLeft();
    while (i != nullptr)
    {

        output += enumword ;
        output += " ";



        if (i->Length() == 1){
            output += "$";
            output += lv_3_tree_name;
            output += "(";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += ")";
            output += "$ ";
            output += " has degree ";
            output += Latex(rho.domain.Degree(i));
        }
        else{

            output += "$";
            output += lv_3_tree_name;
            output += "_{\\tree}(";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += ")";
            output += "=$ ";

            output += "";

            if (rho.domain.Degree(i->Parent()) == DEGREE::ONE){
                output += "the unique completion of $";
                output += lv_3_tree_name;
                output += "(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")$";
            }
            else{
                output += "the completion of $";
                output += lv_3_tree_name;
                output += "(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")$";
                output += " that sends $";

                auto && critical_leq_2_tree_parent = rho.domain.Value(i->Parent());

                auto hanging_sequence = critical_leq_2_tree_parent.CreateHangingSequence();

                auto hanging_minus = hanging_sequence;
                if (std::get<0>(hanging_minus) == DEGREE::ONE){
                        std::get<1>(hanging_minus).pop_back();}
                else{
                        std::get<2>(hanging_minus).pop_back();}

                output += Latex(hanging_sequence);
                output += "$ to the completion of $";
                output += lv_3_tree_name;
                output += "_{\\tree}(";
                output += Latex(rho.domain.EntireEntryInDomain(i->Parent()));
                output += ")";
                output += "";
                output += Latex(hanging_minus);
                output += "$ ";
                output += " whose node component is $";



                auto && Ww = rho.domain.Partial(i);
                auto && w = Ww.NodeMinusInTree();
                if (w == nullptr){
                    output += "-1$";
                }
                else{
                    output += Latex(Ww.CreateHangingSequence());
                    output += "$";
                }
            }

            output += "\n\n\\noindent";

            output += "$";
            output += lv_3_tree_name;
            output += "_{\\node}";
            output += Latex (rho.domain.EntireEntryInDomain (i) );
            output += "";
            output += "= ";

            output += Latex(rho.domain.Value(i).CreateHangingSequence());

            output += "$";
        }


        output += "\n\n";

output += "$\\langle\\langle";
             output += factor_name;
            output += Latex (rho.domain.EntireEntryInDomain (i) );            
             output += "\\rangle\\rangle";
            output += "=$";
            
        output += LatexRep (j->LastEntry().second);
        output += "\n\n";
        i = i->BKLeft();
        j = j->BKLeft();        
        
        output += "\n\n";

output += "$\\langle\\langle";
             output += factor_prime_name;
            output += Latex (rho_prime.domain.EntireEntryInDomain (i_prime) );            
             output += "\\rangle\\rangle";
            output += "=$";
            
        output += LatexRep (j_prime->LastEntry().second);
        output += "\n\n";
        i_prime = i_prime->BKLeft();
        j_prime = j_prime->BKLeft();
    }
    return output;
}

string LatexTensorProduct (const Level_leq_2_Tree & T,
                           const Level_leq_2_Tree & Q,
                           const Level_leq_2_Tree & U){
    string output;
    output += "A representation of $T \\otimes Q$ is $X$, and $\\pi_X$ is a \"level $\\leq 2$ tree isomorphism\" between $X$ and  $T \\otimes Q$, given as follows:\n"                          ;
    output += "\\begin{itemize}";
    auto && TQ = TensorProduct(T,Q);
    output += LatexRep (TQ,
                        "X",
                        "\\pi_X",
                        "\\item");
    output += "\\end{itemize}";    
    
    output += "A representation of $Q \\otimes U$ is $M$, and $\\pi_M$ is a \"level $\\leq 2$ tree isomorphism\" between $M$ and  $Q \\otimes U$, given as follows:\n"                          ;
    output += "\\begin{itemize}";
    auto && QU = TensorProduct(Q,U);
    output += LatexRep (QU,
                        "M",
                        "\\pi_M",
                        "\\item");
    output += "\\end{itemize}";
    
    output += "Both $(T \\otimes Q) \\otimes U$ and $T \\otimes (Q \\otimes U)$ can be represented by the tree $N$. ";
    output += "Let $\\psi$ be the \"level $\\leq 2$ tree isomorphism\" between $N$ and  $X \\otimes U$ and ";
    output += "let $\\psi'$ be the \"level $\\leq 2$ tree isomorphism\" between $N$ and  $T \\otimes M$.";
    output += "Then $N$ and $\\psi$, $\\psi'$ are as follows:\n";
    output += "\\begin{etaremune}\n";
    output += LatexRepDual(TensorProduct(TQ.domain, U),
                           TensorProduct(T, QU.domain),
                           "N",
                           "\\psi",
                           "\\psi'",
                           "\\item"
                           );
    output += "\n\\end{etaremune}";
    return output;
}

string LatexTensorProduct (const LevelThreeTree & Y,
                           const Level_leq_2_Tree & T,
                           const Level_leq_2_Tree & Q){
    string output;
    output += "A representation of $Y \\otimes T$ is $R$, and $\\rho_R$ is a \"level-3 tree isomorphism\" between $R$ and  $Y \\otimes T$, given as follows:\n"                          ;
    output += "\\begin{itemize}";
    auto && YT = TensorProduct(Y,T);
    output += LatexRep (YT,
                        "R",
                        "\\rho_R",
                        "\\item");
    output += "\\end{itemize}";    
    
    output += "A representation of $T \\otimes Q$ is $M$, and $\\pi_M$ is a \"level $\\leq 2$ tree isomorphism\" between $M$ and  $T \\otimes Q$, given as follows:\n"                          ;
    output += "\\begin{itemize}";
    auto && TQ = TensorProduct(T,Q);
    output += LatexRep (TQ,
                        "M",
                        "\\pi_M",
                        "\\item");
    output += "\\end{itemize}";
    
    output += "Both $(Y \\otimes T) \\otimes Q$ and $Y \\otimes (T \\otimes Q)$ can be represented by the tree $N$. ";
    output += "Let $\\psi$ be the \"level-3 tree isomorphism\" between $N$ and  $R \\otimes Q$ and ";
    output += "let $\\psi'$ be the \"level-3 tree isomorphism\" between $N$ and  $Y \\otimes M$.";
    output += "Then $N$ and $\\psi$, $\\psi'$ are as follows:\n";
    output += "\\begin{etaremune}\n";
    output += LatexRepDual(TensorProduct(YT.domain, Q),
                           TensorProduct(Y, TQ.domain),
                           "N",
                           "\\psi",
                           "\\psi'",
                           "\\item"
                           );
    output += "\n\\end{etaremune}";
    return output;
}

#endif // LATEX_H_INCLUDED
