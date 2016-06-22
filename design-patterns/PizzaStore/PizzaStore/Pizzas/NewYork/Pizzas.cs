using PizzaStore.Ingredients;

namespace PizzaStore.Pizzas.NewYork
{
    public class CheesePizza : Pizzas.CheesePizza
    {
        public CheesePizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory)
        {
            Name = "NY Style Sauce and Cheese Pizza";
            Dough = "Thin Crust Dough";
            Sauce = "Marinara Sauce";
            toppings.Add("Grated Reggiano Cheese");
        }
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
