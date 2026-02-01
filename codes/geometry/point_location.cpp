int cross_product = a.orient(b, c);
if(cross_product > 0){
    cout<< "LEFT" << endl;
}
else if(cross_product < 0){
    cout<<"RIGHT" <<endl;
}
else{
    cout<<"TOUCH"<<endl;
}