#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
class Polynomial;
class Error{
private:
    string error_massage;
public:
    Error(string mes)
    {
        error_massage=mes;
    }
    void print()
    {
        cout<<error_massage;
    }

};

class term{
private:
    int p;
    float c;
    string vorodi;
public:
    term()
    {

    }
    term(float c1,int p1);
    term operator-();

    term operator+(float);
    term operator+(term &T);
    friend term operator+(float ,term &T);

    term operator-(float);
    term operator-(term &T);
    friend term operator-(float ,term &T);

    term operator*(float);
    term operator*(term &T);
    friend term operator*(float ,term &T);

    term operator/(float);
    term operator/(term &T);
    friend term operator/(float ,term &T);

    term operator +=(float);
    term operator +=(term &);
    friend term operator +=(float,term &T);

    term operator -=(float);
    term operator -=(term &);
    friend term operator -=(float,term &T);

    term operator *=(float);
    term operator *=(term &);
    friend term operator *=(float,term &T);

    term operator /=(float);
    term operator /=(term &);
    friend term operator /=(float,term &T);

    bool operator ==(term &T);
    bool operator ==(float);
    friend bool operator ==(float,term &T);

    bool operator !=(term &T);
    bool operator !=(float);
    friend bool operator !=(float,term &T);

    bool operator >(term &T);
    bool operator >(float);
    friend bool operator >(float,term &T);

    bool operator >=(term &T);
    bool operator >=(float);
    friend bool operator >=(float,term &T);

    bool operator <(term &T);
    bool operator <(float);
    friend bool operator <(float,term &T);

    bool operator <=(term &T);
    bool operator <=(float);
    friend bool operator <=(float,term &T);

    term operator ~();

    term operator ++();
    term operator ++(int);

    term operator --();
    term operator --(int);

    float operator()(float);

    friend ostream &operator <<(ostream &out, term &);
    friend istream &operator >>(istream &in, term &);

    float get_power()
    {
        return p;
    }
    int get_c()
    {
        return c;
    }
    void set_c(float a)
    {
        c=a;
    }
    void set_power(int a)
    {
        p=a;
    }
};
term::term(float c1,int p1):p(p1),c(c1){};
term term::operator-()
{
    this->c=-this->c;
    return *this;
}



// (+)
term term::operator+(float value)
{
    if(p==0)
    {
        this->p=0;
        this->c+=value;
        return *this;
    }
    else if(c==0)
    {
        this->c=value;
        this->p=0;
        return *this;
    }
    throw Error("you can not plus float with number with power\n");
}
term term::operator+(term &T)
{
    if(T.p==this->p)
    {
        c+=T.c;
        return *this;
    }
    if(T.c==0)
    {
        return term(c,p);
    }
    else if(c==0)
    {
        return term(T.c,T.p);
    }

    throw Error("you can not + two object with difrent power\n");
}
term operator+(float value,term &T)
{
    if(T.c==0)
    {
        return term(value,0);
    }
    else if(T.p==0)
    {
        return term(T.c+value,0);
    }
    throw  Error("you can not plus float with number with power\n");
}




// (-)
term term::operator-(float value)
{
    if(this->c==0)
    {
        this->c=-value;
        this->p=0;
        return *this;
    }
    else if(this->p==0)
    {
        this->c-=value;
        return *this;
    }
    throw  "you can not - float with number with power\n";
}
term term::operator-(term &T)
{
    if(T.p==this->p)
    {
        this->c -= T.c;
        return *this;
    }
    else if(T.c==0)
    {
        return term(c,p);
    }
    else if(c==0)
    {
        return term(-T.c,T.p);
    }

    throw "you can not - two object with difrent power\n";
}
term operator-(float value,term &T)
{
    if(T.c==0)
    {
        return term(value,0);
    }
    else if(T.p==0)
    {
        return term(value-T.c,0);
    }
    throw  "you can not - float with number with power\n";
}



// (*)
term term::operator*(float value)
{
    return term(c*value,p);
}
term term::operator*(term &T)
{
    //    this->c*=T.c;
    //    this->p+=T.p;
    //    return *this;
    return term(c*T.c,p+T.p);
}
term operator*(float value,term &T)
{
    return term( value * T.c , T.p);
}



// (/)
term term::operator/(float value)
{
    if(value==0)
    {
        throw "division by zero\n";
    }
    return term(this->c/value,this->p);
}
term term::operator/(term &T)
{
    if(T.c==0)
    {
        throw "division by zero\n";
    }
    return term(this->c/T.c,this->p-T.p);
}
term operator/(float value,term &T)
{
    if(T.c==0)
    {
        throw "division by zero\n";
    }
    return term(value/T.c,-T.p);
}




// (+=)
term term::operator+=(float value)
{
    if(this->c==0)
    {
        this->c=value;
        this->p=0;
        return *this;
    }
    else if(this->p==0)
    {
        this->c+=value;
        this->p=0;
        return *this;
    }
    throw  Error("you can not += float with number with power\n");
}
term term::operator+=(term &T)
{
    if(T.p==this->p)
    {
        c+=T.c;
        return *this;
    }
    throw Error("you can not += two object with difrent power\n");
}
term operator +=(float value,term &T)
{
    if(T.c==0)
    {
        return term(value,0);
    }
    else if(T.p==0)
    {
        return term(T.c+value,0);
    }
    throw  Error("you can not += float with number with power\n");
}



// (-=)
term term::operator-=(float value)
{
    if(this->c==0)
    {
        this->c=-value;
        this->p=0;
        return *this;
    }
    else if(this->p==0)
    {
        this->c-=value;
        return *this;
    }
    throw  Error("you can not -= float with number with power\n");
}
term term::operator-=(term &T)
{

    if(T.p==this->p)
    {
        c-=T.c;
        return *this;
    }
    throw Error("you can not -= two object with difrent power\n");
}
term operator-=(float value,term &T)
{
    if(T.c==0)
    {
        return term(value,0);
    }
    else if(T.p==0)
    {
        return term(value-T.c,0);
    }
    throw  Error("you can not -= float with number with power\n");
}




// (*=)
term term::operator *=(float value)
{
    this->c*=value;
    return *this;
}
term term::operator *=(term &T)
{
    this->c*=T.c;
    this->p+=T.p;
    return *this;
}
term operator *=(float value,term &T)
{
    T.c*=value;
    return term( T.c , T.p);
}



// (/=)
term term::operator /=(float value)
{
    if(value==0)
    {
        throw "division by zero\n";
    }
    this->c/=value;
    return term(this->c,this->p);
}
term term::operator /=(term &T)
{
    if(T.c==0)
    {
        throw "division by zero\n";
    }
    this->c/=T.c;
    this->p-=T.p;
    return term(this->c,this->p);
}
term operator /=(float value,term &T)
{
    if(T.c==0)
    {
        throw "division by zero\n";
    }
    value/=T.c;
    T.p=-T.p;
    return term(value,T.p);
}


// (==)
bool term::operator==(term &T)
{
    if(this->c==T.c && this->p==T.p)
    {
        return true;
    }
    return false;
}
bool term::operator==(float value)
{
    if(this->c==value && this->p==0)
    {
        return true;
    }
    return false;
}
bool operator ==(float value,term &T)
{
    if(value==T.c && T.p==0)
    {
        return true;
    }
    return false;
}



// (!=)
bool term::operator!=(term &T)
{
    if(this->c!=T.c || this->p!=T.p)
    {
        return true;
    }
    return false;
}
bool term::operator != (float value)
{
    if(this->c!=value || this->p!=0)
    {
        return true;
    }
    return false;
}
bool operator !=(float value,term &T)
{
    if(value != T.c || T.p!=0)
    {
        return true;
    }
    return false;
}



// (>)
bool term::operator>(term &T)
{
    if(T.p<this->p)
    {
        return true;
    }
    else if(T.p==this->p && T.c<this->c)
    {
        return true;
    }
    return false;
}
bool term::operator>(float value)
{
    if(this->p==0 && this->c>value)
    {
        return true;
    }
    else if(this->p>0)
    {
        return true;
    }
    return false;
}
bool operator >(float value,term &T)
{
    if(T.p==0 && T.c<value)
    {
        return true;
    }
    else if(T.p>0)
    {
        return true;
    }
    return false;
}



// (>=)
bool term::operator>=(term &T)
{
    if(T.p<=this->p)
    {
        return true;
    }
    else if(T.p==this->p && T.c<=this->c)
    {
        return true;
    }
    return false;
}
bool term::operator>=(float value)
{
    if(this->p==0 && this->c>=value)
    {
        return true;
    }
    else if(this->p>0)
    {
        return true;
    }
    return false;
}
bool operator >=(float value,term &T)
{
    if(T.p==0 && T.c<=value)
    {
        return true;
    }
    else if(T.p>0)
    {
        return true;
    }
    return false;
}




// (<)
bool term::operator<(term &T)
{
    if(T.p>this->p)
    {
        return true;
    }
    else if(T.p==this->p && T.c>this->c)
    {
        return true;
    }
    return false;
}
bool term::operator<(float value)
{
    if(this->p==0 && this->c<value)
    {
        return true;
    }
    else if(this->p<0)
    {
        return true;
    }
    return false;
}
bool operator <(float value,term &T)
{
    if(T.p==0 && T.c>value)
    {
        return true;
    }
    else if(T.p>0)
    {
        return true;
    }
    return false;
}



// (<=)
bool term::operator<=(term &T)
{
    if(T.p>=this->p)
    {
        return true;
    }
    else if(T.p==this->p && T.c>=this->c)
    {
        return true;
    }
    return false;
}
bool term::operator<=(float value)
{
    if(this->p==0 && this->c<=value)
    {
        return true;
    }
    else if(this->p<0)
    {
        return true;
    }
    return false;
}
bool operator <=(float value,term &T)
{
    if(T.p==0 && T.c>=value)
    {
        return true;
    }
    else if(T.p>0)
    {
        return true;
    }
    return false;
}



// (~)
term term::operator~()
{
    if(this->p==0)
    {
        return term(0,0);
    }
    else
    {
        return term(c*p,p-1);
    }
}



// (++)
term term::operator++()
{
    if(this->p==0)
    {
        this->c+=1;
        this->p=0;
        return *this;
    }
    throw Error("you can not ++ number with power\n");
}
term term::operator ++(int)
{
    if(p==0)
    {
        term temp=*this;
        c++;
        p=0;
        return temp;
    }
    throw Error("you can not ++ number with power\n");
}


// (--)
term term::operator--()
{
    if(this->p==0)
    {
        this->c-=1;
        this->p=0;
        return *this;
    }
    throw Error("you can not -- number with power\n");
}
term term::operator--(int)
{
    if(p==0)
    {
        term temp=*this;
        c--;
        p=0;
        return temp;
    }
    throw Error("you can not -- number with power\n");
}


float term::operator()(float value)
{
    return this->c * pow(value,this->p);
}


ostream &operator <<(ostream &output, term &T)
{
    if(T.c==1 && T.p==1)
    {
        output<<"x ";
    }
    else if(T.c==0)
    {

    }
    else if(T.p==0)
    {
        output<<T.c<<" ";
    }
    else if(T.p==1)
    {
        if(T.c==-1)
        {
            output<<"-x ";
        }
        else
        {
            output<<T.c<<"x ";
        }
    }
    else if(T.c==-1 && T.p!=1)
    {
        output<<"-x^"<<T.p<<" ";
    }
    else if(T.c==1)
    {
        output<<"x^"<<T.p<<" ";
    }
    else
    {
        output<<T.c<<"x^"<<T.p<<" ";
    }
    return output;

}

istream &operator >>(istream &input, term &T)
{
    input>>T.vorodi;
    int pos=T.vorodi.find('x');
    int size=T.vorodi.size();
    bool check=false;
    for(int i=0; i<size; i++)
    {
        if(pos==-1)
        {
            int counter=0;
            for(int i=0; i<size; i++)
            {
                if(!isalpha(T.vorodi[i]))
                {
                    counter+=1;
                }
            }
            if(counter==size)
            {
                T.c=stof(T.vorodi.substr(0));
                T.p=0;
                check=true;
                break;
            }
        }
        else
        {
            if(T.vorodi[0]=='x' )
            {
                if(T.vorodi[1]==NULL)
                {
                    T.c=1;
                    T.p=1;
                }
                else if(T.vorodi[1]=='^' && T.vorodi[2]!=NULL)
                {
                    T.c=1;
                    T.p=stof(T.vorodi.substr(2));
                }
                check=true;
                break;
            }

            else if(T.vorodi[0]!='x')
            {
                int count=0;
                int count2=0;

                for(int j=0; j<pos; j++)
                {
                    if(!isalpha(T.vorodi[j]))
                    {
                        count+=1;
                    }
                    if(T.vorodi[0]=='-' or T.vorodi[0]=='+')
                    {
                        count2+=1;
                    }
                }

                if(count2==1 && count==pos)
                {
                    if(T.vorodi[0]=='-')
                    {
                        T.c=-1;
                        if(T.vorodi[pos+1]!=NULL)
                        {
                            if(T.vorodi[pos+1]=='^' && T.vorodi[pos+2]!=NULL)
                            {
                                T.p=stof(T.vorodi.substr(pos+2));
                            }
                        }
                        else
                        {
                            T.p=1;
                        }
                        check=true;
                        break;

                    }
                    else if(T.vorodi[0]=='+')
                    {
                        T.c=1;
                        if(T.vorodi[pos+1]!=NULL)
                        {
                            T.p=stof(T.vorodi.substr(pos+1));
                        }
                        else
                        {
                            T.p=1;
                        }

                    }
                    check=true;
                    break;

                }

                else if(count==pos)
                {
                    T.c=stof(T.vorodi.substr(0,pos));
                    if(T.vorodi[pos+1]=='^' && T.vorodi[pos+2]!=NULL)
                    {
                        T.p=stof(T.vorodi.substr(pos+2));
                    }
                    else if(T.vorodi[pos+1]==NULL)
                    {
                        T.p=1;
                    }
                    check=true;
                    break;
                }
            }
        }
    }

    if(check)
    {
        return input;
    }
    else
    {
        throw  Error("incorrect input !\n");
    }
}


class Polynomial
{
private:
    vector<term> pol;
public:
    void sort()
    {
        int size=pol.size();
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size-i-1; j++)
            {
                if(pol.at(j).get_power()<pol.at(j+1).get_power())
                {
                    swap(pol.at(j),pol.at(j+1));
                }
            }
        }
    }
    Polynomial(vector<term> &po): pol(po){}
    Polynomial(){}
    Polynomial operator +(term &);
    friend Polynomial operator +(term &,Polynomial &);
    Polynomial operator +(Polynomial &);
    Polynomial operator +(float);
    friend Polynomial operator +(float,Polynomial &);

    Polynomial operator -(term &);
    friend Polynomial operator -(term &,Polynomial &);
    Polynomial operator -(Polynomial &);
    Polynomial operator -(float);
    friend Polynomial operator -(float,Polynomial &);

    Polynomial operator *(term &);
    friend Polynomial operator *(term &,Polynomial &);
    Polynomial operator *(Polynomial &);
    Polynomial operator *(float);
    friend Polynomial operator *(float,Polynomial &);

    Polynomial operator +=(Polynomial &);

    Polynomial operator -=(Polynomial &);

    Polynomial operator *=(Polynomial &);

    bool operator >(term &);
    friend bool operator >(term &,Polynomial &);
    bool operator >(Polynomial &);
    bool operator >(float);
    friend bool operator >(float,Polynomial &);

    bool operator <(term &);
    friend bool operator <(term &,Polynomial &);
    bool operator <(Polynomial &);
    bool operator <(float);
    friend bool operator <(float,Polynomial &);

    bool operator >=(term &);
    friend bool operator >=(term &,Polynomial &);
    bool operator >=(Polynomial &);
    bool operator >=(float);
    friend bool operator >=(float,Polynomial &);

    bool operator <=(term &);
    friend bool operator <=(term &,Polynomial &);
    bool operator <=(Polynomial &);
    bool operator <=(float);
    friend bool operator <=(float,Polynomial &);

    bool operator ==(term &);
    friend bool operator ==(term &,Polynomial &);
    bool operator ==(Polynomial &);
    bool operator ==(float);
    friend bool operator ==(float,Polynomial &);

    bool operator !=(term &);
    friend bool operator !=(term &,Polynomial &);
    bool operator !=(Polynomial &);
    bool operator !=(float);
    friend bool operator !=(float,Polynomial &);

    Polynomial operator ~();

    float operator ()(float);

    const term operator[](int );
    term& operator[](int &);

    Polynomial operator ++();
    Polynomial operator ++(int);

    Polynomial operator --();
    Polynomial operator --(int);

    friend ostream &operator<<(ostream &output,Polynomial &);
    friend istream &operator >>(istream &input, Polynomial &);

    friend int find_Degree(Polynomial &);

    friend int find_number_of_term(Polynomial &);

    friend void write_text_file(Polynomial &);
    friend void write_binary_file(Polynomial &);

    friend void read_text_file(Polynomial &);
    friend void read_binary_file(Polynomial &);
};


// (+)
Polynomial Polynomial::operator+(term &T)
{
    vector<term> po=pol;
    int size=po.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(po[i].get_power()==T.get_power())
        {
            temp=1;
            po[i]+=T;
            break;
        }
    }
    if(temp==0)
    {
        po.push_back(T);
    }
    return Polynomial(po);
}
Polynomial operator +(term &T,Polynomial &P)
{
    vector<term> po=P.pol;
    int size=po.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(po.at(i).get_power()==T.get_power())
        {
            temp=1;
            po.at(i)+=T;
            break;
        }
    }
    if(temp==0)
    {
        po.push_back(T);
    }
    return Polynomial(po);
}
Polynomial Polynomial::operator+(Polynomial &P)
{
    vector<term> T;
    int size=P.pol.size();
    int size2=pol.size();
    for(int i=0; i<size; i++)
    {
        bool check=true;
        for(int j=0; j<size2 && check==true; j++)
        {
            if(P.pol.at(i).get_power()==pol.at(j).get_power())
            {
                T.push_back(P.pol.at(i)+pol.at(j));
                check=false;
            }
        }
        if(check)
        {
            T.push_back(P.pol.at(i));
        }
    }
    for(int i=0; i<size2; i++)
    {
        bool check=true;
        for(int j=0; j<size && check; j++)
        {
            if(P.pol.at(j).get_power()==pol.at(i).get_power())
            {
                check=false;
            }
        }
        if(check)
        {
            T.push_back(pol.at(i));
        }
    }
    return Polynomial(T);
}
Polynomial Polynomial::operator+(float value)
{
    int temp=0;
    vector<term> po=pol;
    int size=po.size();
    for(int i=0; i<size; i++)
    {
        if(po.at(i).get_power()==0)
        {
            temp=1;
            po[i]+=value;
            break;
        }
    }
    if(temp==0)
    {
        po.push_back(term(value,0));
    }
    return Polynomial(po);
}
Polynomial operator +(float value,Polynomial &P)
{
    vector<term> po=P.pol;
    int size=po.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(po.at(i).get_power()==0)
        {
            temp=1;
            po.at(i)+=value;
            break;
        }
    }
    if(temp==0)
    {
        po.push_back(term(value,0));
    }
    return Polynomial(po);
}



// (-)
Polynomial Polynomial::operator-(term &T)
{
    vector<term> po=pol;
    int size=po.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(po[i].get_power()==T.get_power())
        {
            temp=1;
            po[i]-=T;
            break;
        }
    }
    if(temp==0)
    {
        po.push_back(-T);
    }
    return Polynomial(po);
}
Polynomial operator -(term &T,Polynomial &P)
{
    vector<term> po=P.pol;
    int size=po.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(po.at(i).get_power()==T.get_power())
        {
            temp=1;
            for(int j=0; j<size; j++)
            {
                po.at(j)=-po.at(j);
            }
            po.at(i)=T+po.at(i);
            break;
        }
    }
    if(temp==0)
    {
        for(int i=0; i<size; i++)
        {
            po.at(i)=-po.at(i);
        }
        po.push_back(T);
    }
    return Polynomial(po);
}
Polynomial Polynomial::operator-(Polynomial &P)
{
    vector<term> T;
    int size1=pol.size();
    int size2=P.pol.size();
    for(int i=0; i<size1; i++)
    {
        bool check=true;
        for(int j=0; j<size2 && check; j++)
        {
            if(pol.at(i).get_power()==P.pol.at(j).get_power())
            {
                T.push_back(pol.at(i)-P.pol.at(j));
                check=false;
            }
        }
        if(check)
        {
            T.push_back(pol.at(i));
        }
    }
    for(int i=0; i<size2; i++)
    {
        bool check=true;
        for(int j=0; j<size1 &&  check; j++)
        {
            if(P.pol.at(i).get_power()==pol.at(j).get_power())
            {
                check=false;
            }
        }
        if(check)
        {
            T.push_back(-P.pol.at(i));
        }
    }
    return Polynomial(T);
}
Polynomial Polynomial::operator-(float value)
{
    vector<term> T=pol;
    int size=T.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(T.at(i).get_power()==0)
        {
            temp=1;
            T.at(i)-=value;
            break;
        }
    }
    if(temp==0)
    {
        T.push_back(term(-value,0));
    }
    return Polynomial(T);
}
Polynomial operator -(float value,Polynomial &P)
{
    vector<term> T=P.pol;
    int size=T.size();
    int temp=0;
    for(int i=0; i<size; i++)
    {
        if(T.at(i).get_power()==0)
        {
            temp=1;
            for(int j=0; j<size; j++)
            {
                T.at(j)=-T.at(j);
            }
            T.at(i)=value+T.at(i);
            break;
        }
    }
    if(temp==0)
    {
        for(int j=0; j<size; j++)
        {
            T.at(j)=-T.at(j);
        }
        T.push_back(term(value,0));
    }
    return Polynomial(T);
}



// (*)
Polynomial Polynomial::operator*(term &T)
{
    vector<term> po;
    int size=pol.size();
    for(int i=0; i<size; i++)
    {
        po.push_back(T*pol.at(i));
    }
    return Polynomial(po);
}
Polynomial operator *(term &T,Polynomial &P)
{
    vector<term> po;
    int size=P.pol.size();
    for(int i=0; i<size; i++)
    {
        po.push_back(T*P.pol.at(i));
    }
    return Polynomial(po);
}
Polynomial Polynomial::operator*(Polynomial &P)
{
    vector<term> T1;
    vector<term> T2;
    int size1=pol.size();
    int size2=P.pol.size();
    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            T1.push_back(pol.at(i)*P.pol.at(j));
        }
    }
    int size3=T1.size();
    for(int i=0; i<size3; i++)
    {
        bool check=false;
        for(int j=i+1; j<size3 && T1.at(i).get_c()!=0; j++)
        {

            if(T1.at(i).get_power()==T1.at(j).get_power() )
            {
                check=true;
                T1.at(i)+=T1.at(j);
                T1.at(j).set_c(0);
            }
        }
        if(check)
        {
            T2.push_back(T1.at(i));
            T1.at(i).set_c(0);
        }
    }
    for(int i=0; i<size3; i++)
    {
        if(T1.at(i).get_c()!=0 )
        {
            T2.push_back(T1.at(i));
        }
    }

    return Polynomial(T2);
}
Polynomial Polynomial::operator*(float value)
{
    vector<term> po;
    int size=pol.size();
    for(int i=0; i<size; i++)
    {
        po.push_back(value*pol.at(i));
    }
    return Polynomial(po);
}
Polynomial operator *(float value,Polynomial &P)
{
    vector<term> po;
    int size=P.pol.size();
    for(int i=0; i<size; i++)
    {
        po.push_back(value*P.pol.at(i));
    }
    return Polynomial(po);
}



// (+=)
Polynomial Polynomial::operator+=(Polynomial &P)
{
    vector<term> T=P.pol;
    int size2=T.size();
    int size1=pol.size();
    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            if(pol.at(i).get_power()==T.at(j).get_power())
            {
                pol.at(i)+=T.at(j);
                T.at(j).set_c(0);
            }
        }
    }
    for(int i=0; i<size2; i++)
    {
        if(T.at(i).get_c()!=0)
        {
            pol.push_back(T.at(i));
        }
    }
    return Polynomial(T);
}




// (-=)
Polynomial Polynomial::operator-=(Polynomial &P)
{
    vector<term> T=P.pol;
    int size2=T.size();
    int size1=pol.size();
    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            if(pol.at(i).get_power()==T.at(j).get_power())
            {
                pol.at(i)-=T.at(j);
                T.at(j).set_c(0);
            }
        }
    }
    for(int i=0; i<size2; i++)
    {
        if(T.at(i).get_c()!=0)
        {
            pol.push_back(-T.at(i));
        }
    }
    return Polynomial(T);
}



// (*=)
Polynomial Polynomial::operator *=(Polynomial &P)
{
    vector<term> T1;
    vector<term> T2;
    int size1=pol.size();
    int size2=P.pol.size();
    for(int i=0; i<size1; i++)
    {
        for(int j=0; j<size2; j++)
        {
            T1.push_back(pol.at(i)*P.pol.at(j));
        }
    }
    int size3=T1.size();
    for(int i=0; i<size3; i++)
    {
        bool check=false;
        for(int j=i+1; j<size3 && T1.at(i).get_c()!=0; j++)
        {

            if(T1.at(i).get_power()==T1.at(j).get_power() )
            {
                check=true;
                T1.at(i)+=T1.at(j);
                T1.at(j).set_c(0);
            }
        }
        if(check)
        {
            T2.push_back(T1.at(i));
            T1.at(i).set_c(0);
        }
    }
    for(int i=0; i<size3; i++)
    {
        if(T1.at(i).get_c()!=0 )
        {
            T2.push_back(T1.at(i));
        }
    }
    pol=T2;
    return Polynomial(pol);
}



//(>)
bool Polynomial::operator>(term &T)
{
    if(pol.at(0)>T)
    {
        return true;
    }
    return false;
}
bool operator >(term &T,Polynomial &P)
{
    if(T>P.pol.at(0))
    {
        return true;
    }
    return false;

}
bool Polynomial::operator>(Polynomial &P)
{
    if(pol.at(0)>P.pol.at(0))
    {
        return true;
    }
    return false;
}
bool Polynomial::operator>(float value)
{
    if(pol.at(0)>value)
    {
        return true;
    }
    return false;
}
bool operator >(float value,Polynomial &P)
{
    if(value>P.pol.at(0))
    {
        return true;
    }
    return false;
}



// (<)
bool Polynomial::operator<(term &T)
{
    if(pol.at(0)<T)
    {
        return true;
    }
    return false;
}
bool operator <(term &T,Polynomial &P)
{
    if(T<P.pol.at(0))
    {
        return true;
    }
    return false;

}
bool Polynomial::operator<(Polynomial &P)
{
    if(pol.at(0)<P.pol.at(0))
    {
        return true;
    }
    return false;
}
bool Polynomial::operator<(float value)
{
    if(pol.at(0)<value)
    {
        return true;
    }
    return false;
}
bool operator <(float value,Polynomial &P)
{
    if(value<P.pol.at(0))
    {
        return true;
    }
    return false;
}



//(>=)
bool Polynomial::operator>=(term &T)
{
    if(pol.at(0)>=T)
    {
        return true;
    }
    return false;
}
bool operator >=(term &T,Polynomial &P)
{
    if(T>=P.pol.at(0))
    {
        return true;
    }
    return false;

}
bool Polynomial::operator>=(Polynomial &P)
{
    if(pol.at(0)>=P.pol.at(0))
    {
        return true;
    }
    return false;
}
bool Polynomial::operator>=(float value)
{
    if(pol.at(0)>=value)
    {
        return true;
    }
    return false;
}
bool operator >=(float value,Polynomial &P)
{
    if(value>P.pol.at(0))
    {
        return true;
    }
    return false;
}




// (<=)
bool Polynomial::operator<=(term &T)
{
    if(pol.at(0)<=T)
    {
        return true;
    }
    return false;
}
bool operator <=(term &T,Polynomial &P)
{
    if(T<=P.pol.at(0))
    {
        return true;
    }
    return false;

}
bool Polynomial::operator<=(Polynomial &P)
{
    if(pol.at(0)<=P.pol.at(0))
    {
        return true;
    }
    return false;
}
bool Polynomial::operator<=(float value)
{
    if(pol.at(0)<=value)
    {
        return true;
    }
    return false;
}
bool operator <=(float value,Polynomial &P)
{
    if(value<=P.pol.at(0))
    {
        return true;
    }
    return false;
}



// (==)
bool Polynomial::operator==(term &T)
{
    int size=pol.size();
    if(size==1 && pol.at(0)==T)
    {
        return true;
    }
    return false;
}
bool operator ==(term &T,Polynomial &P)
{
    int size=P.pol.size();
    if(size==1 && P.pol.at(0)==T)
    {
        return true;
    }
    return false;
}
bool Polynomial::operator==(Polynomial &P)
{
    int size1=pol.size();
    int size2=P.pol.size();
    int temp=0;
    if(size1==size2)
    {
        for(int i=0; i<size1; i++)
        {
            if(pol.at(i)==P.pol.at(i))
            {
                temp+=1;
            }
        }
    }
    if(temp==size1)
    {
        return true;
    }
    return false;
}
bool Polynomial::operator==(float value)
{
    int size=pol.size();
    if(size==1 && pol.at(0)==value)
    {
        return true;
    }
    return false;
}
bool operator ==(float value,Polynomial &P)
{
    int size=P.pol.size();
    if(size==1 && P.pol.at(0)==value)
    {
        return true;
    }
    return false;
}



// (!=)
bool Polynomial::operator!=(term &T)
{
    int size=pol.size();
    if(size==1 && pol.at(0)==T)
    {
        return false;
    }
    return true;
}
bool operator !=(term &T,Polynomial &P)
{
    int size=P.pol.size();
    if(size==1 && P.pol.at(0)==T)
    {
        return false;
    }
    return true;
}
bool Polynomial::operator!=(Polynomial &P)
{
    int size1=pol.size();
    int size2=P.pol.size();
    int temp=0;
    if(size1==size2)
    {
        for(int i=0; i<size1; i++)
        {
            if(pol.at(i)==P.pol.at(i))
            {
                temp+=1;
            }
        }
    }
    if(temp==size1)
    {
        return false;
    }
    return true;
}
bool Polynomial::operator!=(float value)
{
    int size=pol.size();
    if(size==1 && pol.at(0)==value)
    {
        return false;
    }
    return true;
}
bool operator !=(float value,Polynomial &P)
{
    int size=P.pol.size();
    if(size==1 && P.pol.at(0)==value)
    {
        return false;
    }
    return true;
}



// (~)
Polynomial Polynomial::operator~()
{
    vector<term> T;
    vector<term> T2=pol;
    int size=pol.size();
    term temp(0,0);
    for(int i=0; i<size; i++)
    {
        if(~T2.at(i)!=temp)
        {
            T2.at(i)=~T2.at(i);
            T.push_back(T2.at(i));
        }
    }
    return Polynomial(T);
}



// (())
float Polynomial::operator()(float value)
{
    float f=0;
    int size=pol.size();
    for(int i=0; i<size; i++)
    {
        f=f+pol.at(i)(value);
    }
    return f;

}


// ([])
term &Polynomial::operator[](int &x)
{
    int size=pol.size();
    if(x<size && x>=0)
    {
        return pol.at(x);
    }
    throw Error("out of rang vector size\n");

}
const term Polynomial::operator[](int x)
{
    int size=pol.size();
    if(x<size && x>=0)
    {
        return pol.at(x);
    }
    throw Error("out of rang vector size\n");
}



//(++)
Polynomial Polynomial::operator++()
{
    int size=pol.size();
    int temp=0;
    vector<term> T=pol;
    for(int i=0; i<size; i++)
    {
        if(T.at(i).get_power()==0)
        {
            temp=1;
            T.at(i)+=1;
        }
    }
    if(temp==0)
    {
        term temp2(1,0);
        T.push_back(temp2);
    }
    return Polynomial(T);
}
Polynomial Polynomial::operator++(int)
{
    int size=pol.size();
    int temp=0;
    vector<term> T=pol;
    for(int i=0; i<size; i++)
    {
        if(T.at(i).get_power()==0)
        {
            temp=1;
            T.at(i)+=1;
        }
    }
    if(temp==0)
    {
        term temp2(1,0);
        T.push_back(temp2);
    }
    return Polynomial(T);
}



//(--)
Polynomial Polynomial::operator--()
{
    int size=pol.size();
    int temp=0;
    vector<term> T=pol;
    for(int i=0; i<size; i++)
    {
        if(T.at(i).get_power()==0)
        {
            temp=1;
            T.at(i)-=1;
        }
    }
    if(temp==0)
    {
        term temp2(-1,0);
        T.push_back(temp2);
    }
    return Polynomial(T);
}
Polynomial Polynomial::operator--(int)
{
    int size=pol.size();
    int temp=0;
    vector<term> T=pol;
    for(int i=0; i<size; i++)
    {
        if(T.at(i).get_power()==0)
        {
            temp=1;
            T.at(i)-=1;
        }
    }
    if(temp==0)
    {
        term temp2(-1,0);
        T.push_back(temp2);
    }
    return Polynomial(T);
}



// (<<)
ostream &operator<<(ostream &output,Polynomial &P)
{
    int size=P.pol.size();
    for(int i=0; i<size; i++)
    {
        output<<P.pol.at(i);
    }
    return output;
}
istream &operator >>(istream &input, Polynomial &P)
{
    string str;
    input>>str;
    for(unsigned int i=0; i<str.size(); i++)
    {
        if((str.at(i)<='z' && str.at(i)>='a' && str.at(i)!='x') || (str.at(i)<='Z' && str.at(i)>='A'))
        {
            throw Error("invalid input");
        }
    }
    while(str!="")
    {
        term T;
        string temp;
        int posNeg=str.find('-');
        int posplas=str.find('+');
        if(posplas<posNeg && posplas!=-1)
        {
            temp=str.substr(0,posplas);
            str=str.substr(posplas+1);
        }
        else if(posplas>posNeg && posNeg!=-1)
        {
            if(posNeg==0)
            {
                int posNeg2=(str.substr(posNeg+1)).find('-');
                if(posNeg2!=-1)
                {
                    if(posNeg2<posplas)
                    {
                        temp=str.substr(0,posNeg2+1);
                        str=str.substr(posNeg2+1);
                    }
                    else if(posNeg2>posplas)
                    {
                        temp=str.substr(0,posplas);
                        str=str.substr(posplas+1);
                    }
                }
                else
                {
                    temp=str.substr(0,posplas);
                    str=str.substr(posplas+1);
                }
            }
            else
            {
                temp=str.substr(0,posNeg);
                str=str.substr(posNeg);
            }
        }
        else if(posNeg!=-1 && posplas==-1)
        {
            int posNeg2=(str.substr(posNeg+1)).find('-');
            if(posNeg2!=-1)
            {
                temp=str.substr(0,posNeg2+1);
                str=str.substr(posNeg2+1);
            }
            else if(posNeg==0)
            {
                temp=str;
                str="";
            }
            else
            {
                temp=str.substr(0,posNeg);
                str=str.substr(posNeg);
            }
        }
        else if(posNeg==-1 && posplas!=-1)
        {
            temp=str.substr(0,posplas);
            str=str.substr(posplas+1);
        }
        else if(posNeg==-1 && posplas==-1)
        {
            temp=str;
            str="";
        }
        int key=temp.find('x');
        if(key!=-1)
        {
            if(key!=0)
            {
                if(temp.at(0)=='-' && key==1)
                {
                    T.set_c(-1);
                }
                else
                {
                    T.set_c(stof(temp.substr(0,key).c_str()));
                }
            }
            else
            {
                T.set_c(1);
            }
            int pos_power=temp.find('^');
            if(pos_power!=-1)
            {
                T.set_power(atoi(temp.substr(pos_power+1).c_str()));
            }
            else
            {
                T.set_power(1);
            }
        }
        else
        {
            T.set_c(stof(temp));
            T.set_power(0);
        }
        P.pol.push_back(T);
    }
    for(unsigned int i=0; i<P.pol.size(); i++)
    {
        for(unsigned int j=i+1; j<P.pol.size(); j++)
        {
            if(P.pol.at(i).get_power()==P.pol.at(j).get_power())
            {
                P.pol.at(i)+=P.pol.at(j);
                P.pol.erase(P.pol.begin()+j);
                if(P.pol.size()!=1)
                {
                    --j;
                }
            }
        }
    }
    P.sort();
    return input;

}



int find_Degree(Polynomial &P)
{
    int power;
    power=P.pol.at(0).get_power();
    return power;
}


int find_number_of_term(Polynomial &P)
{
    int x=P.pol.size();
    return x;
}



// write from text file
void write_text_file(Polynomial &P)
{
    int size=P.pol.size();
    ofstream fout("polynomial.txt",ios::trunc);
    if(fout)
    {
        fout<<size<<endl;
        for(unsigned int i=0; i<P.pol.size(); i++)
        {
            fout<<P.pol.at(i);
        }
        cout<<endl<<"file sucsesfully saved"<<endl<<endl;
        fout.close();
    }
    else
    {
        cerr<<"unable to open file"<<endl;
    }
}



// write from binary file
void write_binary_file(Polynomial &P)
{
    ofstream outfile("polynomial.dat",ios::binary | ios::out);
    if(outfile)
    {
        int size=P.pol.size();
        outfile.write((char *)&size ,sizeof(int));
        for(unsigned int i=0; i<P.pol.size(); i++)
        {
            outfile.write((char *)&P.pol.at(i) ,sizeof (term));
        }
        cout<<endl<<"file sucsesfully saved"<<endl<<endl;
        outfile.close();
    }
    else
    {
        cerr<<"unable to open file"<<endl;
    }

}



// read from text file
void read_text_file(Polynomial &P)
{
    ifstream fin("polynomial.txt",ios::in);
    int numbersize;
    if(fin)
    {
        P.pol.clear();
        fin>>numbersize;
        P.pol.resize(numbersize);
        for(int i=0; i<numbersize; i++)
        {
            fin>>P.pol.at(i);
        }
        fin.close();
    }
    else
    {
        cerr<<"unable to open file"<<endl;
    }
}


// read from binary file
void read_binary_file(Polynomial &P)
{
    ifstream finput("polynomial.dat",ios::binary | ios::in);
    int numbersize;
    if(finput)
    {
        P.pol.clear();
        finput.read((char *) &numbersize, sizeof(int));
        P.pol.resize(numbersize);
        for(int i=0; i<numbersize; i++)
        {
            finput.read((char *)&P.pol.at(i),sizeof (term));
        }
        finput.close();
    }
    else
    {
        cerr<<"unable to open file"<<endl;
    }
}
int main()
{
    bool check=true;
    bool check2=true;
    Polynomial current;
    Polynomial test;
    float x;
    while(check)
    {
        int ch;
        cout<<"plese enter your choice :"<<endl;
        cout<<"1 : new polynomial"<<endl;
        cout<<"2 : load from text file"<<endl;
        cout<<"3 : load from binary file"<<endl;
        cout<<"4 : Quit"<<endl;
        cin>>ch;
        switch (ch) {
        case 1:
            check2=true;
            while(check2)
            {
                int ch2;
                cout<<"current polynomial = "<<current<<endl;
                cout<<"plese enter your choice :"<<endl;
                cout<<"1 : Add"<<endl;
                cout<<"2 : Subtract"<<endl;
                cout<<"3 : Multiply"<<endl;
                cout<<"4 : Derivative"<<endl;
                cout<<"5 : find Degree"<<endl;
                cout<<"6 : find value for specific x"<<endl;
                cout<<"7 : compare"<<endl;
                cout<<"8 : Save to text file"<<endl;
                cout<<"9 : Save to a binary file"<<endl;
                cout<<"10: back to main menue"<<endl;
                cin>>ch2;
                switch (ch2) {
                case 1:
                    test=test*0;
                    cout<<"plese enter new polynomial to +"<<endl;
                    try {
                    cin>>test;
                    current+=test;
                    current.sort();
                }catch (Error e) {
                        e.print();
                        cout<<endl;
                    }
                    break;
                case 2:
                    test=test*0;
                    cout<<"plese enter new polynomial to -"<<endl;
                    try {
                    cin>>test;
                    current-=test;
                    current.sort();
                }catch (Error e) {
                        e.print();
                        cout<<endl;
                    }
                    break;
                case 3:
                    test=test*0;
                    cout<<"plese enter new polynomial to *"<<endl;
                    try {
                    cin>>test;
                    current*=test;
                    current.sort();
                }catch (Error e) {
                        e.print();
                        cout<<endl;
                    }
                    break;
                case 4:
                    current=~current;
                    current.sort();
                    break;
                case 5:
                    current.sort();
                    cout<<endl<<"Degree of polynomial is :"<<find_Degree(current)<<endl<<endl;
                    break;
                case 6:
                    cout<<"plese enter number (x=input) :";
                    cin>>x;
                    current.sort();
                    cout<<endl<<"input = "<<current(x)<<endl<<endl;
                    break;
                case 7:
                    cout<<endl;
                    current.sort();
                    test=test*0;
                    cout<<"plese enter polynomial to compare :";
                    try {
                    cin>>test;
                    cout<<"comparing current_polynomial with other_polynomial "<<endl;
                    cout<<"current_polynomial > other_polynomial : ";
                    {
                        if(current>test)
                        {
                            cout<<"true"<<endl;
                        }
                        else
                        {
                            cout<<"false"<<endl;
                        }
                    }

                    {
                        cout<<"current_polynomial >= other_polynomial : ";
                        if(current>=test)
                        {
                            cout<<"true"<<endl;
                        }
                        else
                        {
                            cout<<"false"<<endl;
                        }
                    }

                    {
                        cout<<"current_polynomial < other_polynomial : ";
                        if(current<test)
                        {
                            cout<<"true"<<endl;
                        }
                        else
                        {
                            cout<<"false"<<endl;
                        }
                    }

                    {
                        cout<<"current_polynomial <= other_polynomial : ";
                        if(current<=test)
                        {
                            cout<<"true"<<endl;
                        }
                        else
                        {
                            cout<<"false"<<endl;
                        }
                    }

                    {
                        cout<<"current_polynomial == other_polynomial : ";
                        if(current==test)
                        {
                            cout<<"true"<<endl;
                        }
                        else
                        {
                            cout<<"false"<<endl;
                        }
                    }
                    cout<<endl<<endl;
                }catch (Error e) {
                        e.print();
                        cout<<endl;
                    }
                    break;
                case 8:
                    write_text_file(current);
                    break;
                case 9:
                    write_binary_file(current);
                    break;
                case 10:
                    check2=false;
                    break;
                default:
                    cout<<"your choice is incorrect";
                    cout<<endl<<"try again"<<endl;
                    break;
                }
            }
            break;
        case 2:
            read_text_file(current);
            current.sort();
            break;
        case 3:
            read_binary_file(current);
            current.sort();
            break;
        case 4:
            check=false;
            break;

        }
   \
    }

}

