//

#ifndef _ECS36B_EXCEPTION_
#define _ECS36B_EXCEPTION_

class another
{
private:
  int x;
protected:
public:
};

class ecs36b_Exception : public another
{
private:
protected:
public:
  virtual ~ecs36b_Exception() throw () {};
  virtual const char* what() const throw () { return "Mine"; };
};

#endif /* _ECS36B_EXCEPTION_ */