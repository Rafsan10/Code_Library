bool isLeap(int n){
    if (n%100==0)
        if (n%400==0) return true;
        else return false;
    if (n%4==0) return true;
    else return false;
}
// Num of Leap year in between
int calNum(int year) {
    return (year / 4) - (year / 100) +
    (year / 400);
}
int leapNum(int l, int r) { return calNum(r) - calNum(--l);}