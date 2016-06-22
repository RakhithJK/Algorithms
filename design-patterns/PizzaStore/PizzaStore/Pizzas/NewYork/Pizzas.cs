namespace PizzaStore.Pizzas.NewYork
{
    public class CheesePizza    : Pizzas.CheesePizza {
        public CheesePizza()
        {
            Name  = "NY Style Sauce and Cheese Pizza";
            Dough = "Thin Crust Dough";
            Sauce = "Marinara Sauce";
            toppings.Add("Grated Reggiano Cheese");
        }
    }
    public class PepperoniPizza : Pizzas.CheesePizza { }
    public class VeggiePizza    : Pizzas.CheesePizza { }
    public class ClamPizza      : Pizzas.CheesePizza { }
}
