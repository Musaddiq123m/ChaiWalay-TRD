bool intersect(Point p1,Point p2,Point p3,Point p4){
    int sign1 = (p2 - p1).cross(p3 - p1);
    int sign2 = (p2 - p1).cross(p4 - p1);
    if(( sign1 < 0 and sign2 < 0) or (sign1 > 0 and sign2 > 0)){
        // B is completly on the right or left of A
        return false;
    }
    else{
        int sign3 = (p4 - p3).cross(p1 - p3);
        int sign4 = (p4 - p3).cross(p2 - p3);
        if(( sign3 < 0 and sign4 < 0) or (sign3 > 0 and sign4 > 0)){
            // A is completly on the right or left of B
            return false;
        }
        if (sign1 == 0 && sign2 == 0 && sign3 == 0 && sign4 == 0){
            // the two lines are colienr we have to check if they overlap
            int mnxA = min(p1.x, p2.x), mnxB = min(p3.x, p4.x);
            int mxxA = max(p1.x, p2.x), mxxB = max(p3.x, p4.x);
            int mnyA = min(p1.y, p2.y), mnyB = min(p3.y, p4.y);
            int mxyA = max(p1.y, p2.y), mxyB = max(p3.y, p4.y);
            if(((mnxB >= mnxA and mnxB <= mxxA) or (mnxA >= mnxB and mnxA <= mxxB)) and
                ((mnyB >= mnyA and mnyB <= mxyA) or (mnyA >= mnyB and mnyA <= mxyB))){
                return true;
            }
            else{
                return false;
            }
        }
        else{    
            return true;
        }
        
    }
}