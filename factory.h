#pragma once
#include <map>
#include <memory>

//specific type factory
struct Point
{
private:
   Point(const float x, const float y) : x(x), y(y) {};

   struct PointFactory
   {
   private:
      PointFactory() {};

   public:
      friend class PointFactory;

      static Point NewCartesian(float x, float y) {
         return{ x,y };
      }

      static Point newPolar(float r, float theta) {
         return{ r*cos(theta), r*sin(theta) };
      }
   };


public:
   float x;
   float y;
   static PointFactory Factory;

   ///   Point p = Point::Factory.NewCartesian(1.0f, 1.0f);
};

//abstarct factory
/*DrinkFactory df;
df.makeDrink("coffee");*/

struct HotDrink
{
   virtual void prepare(int vol) = 0;
};
struct HotDrinkFactory
{
   virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct Coffee : HotDrink
{
   virtual void prepare(int vol) override { std::cout << vol << "Coffee has been done!" << '\n'; }
};
struct Tea : HotDrink
{
   virtual void prepare(int vol) override { std::cout << vol << "Tea has been done!" << '\n'; }
};

struct CoffeeFactory : HotDrinkFactory
{
   virtual std::unique_ptr<HotDrink> make() const override { return std::make_unique<Coffee>(); };
};
struct TeaFactory : HotDrinkFactory
{
   virtual std::unique_ptr<HotDrink> make() const override { return std::make_unique<Tea>(); };
};

class DrinkFactory
{
public:
   DrinkFactory()
   {
      hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
      hot_factories["tea"] = std::make_unique<TeaFactory>();
   }

   std::unique_ptr<HotDrink> makeDrink(const char* name) {
      auto drink = hot_factories[name]->make();
      drink->prepare(999);
      return drink;
   }

private:
   std::map<const char*, std::unique_ptr<HotDrinkFactory>> hot_factories;
};
