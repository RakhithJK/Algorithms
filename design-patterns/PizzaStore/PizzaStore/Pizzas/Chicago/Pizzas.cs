using System;
using PizzaStore.Ingredients;

namespace PizzaStore.Pizzas.Chicago
{
    public class CheesePizza : Pizzas.CheesePizza
    {
        public CheesePizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory)
        {
            Name = "Chicago Style Deep Dish Cheese Pizza";
            Dough = "Extra Thick Crust Dough";
            Sauce = "Plum Tomato Sauce";
            toppings.Add("Shredded mozzarella cheese");
            toppings.Add("Shredded mozzarella cheese");
        }
        public override void Cut() => Console.WriteLine("Cutting in square slices!");
    }
    public class PepperoniPizza : Pizzas.CheesePizza
    {
        public PepperoniPizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
    }

    public class VeggiePizza : Pizzas.VeggiePizza
    {
        public VeggiePizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
    }

    public class ClamPizza : Pizzas.ClamPizza
    {
        public ClamPizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
    }
}
