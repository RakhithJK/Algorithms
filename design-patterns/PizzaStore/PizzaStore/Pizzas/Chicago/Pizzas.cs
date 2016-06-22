using System;

namespace PizzaStore.Pizzas.Chicago
{
    public class CheesePizza : Pizzas.CheesePizza
    {
        public CheesePizza()
        {
            Name  = "Chicago Style Deep Dish Cheese Pizza";
            Dough = "Extra Thick Crust Dough";
            Sauce = "Plum Tomato Sauce";
            toppings.Add("Shredded mozzarella cheese");
        }
        public override void Cut() => Console.WriteLine("Cutting in square slices!");
    }
    public class PepperoniPizza : Pizzas.CheesePizza { }
    public class VeggiePizza    : Pizzas.CheesePizza { }
    public class ClamPizza      : Pizzas.CheesePizza { }
}
