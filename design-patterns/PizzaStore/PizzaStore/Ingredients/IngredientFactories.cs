using System.Collections.Generic;

namespace PizzaStore.Ingredients
{
    public interface IPizzaIngredientFactory
    {
        string                  CreateDough();
        string                  CreateSauce();
        string                  CreateCheese();
        IEnumerable<string>     CreateVeggies();
        string                  CreatePepperoni();
        string                  CreateClams();
    }

    public class NewYorkIngredientsFactory : IPizzaIngredientFactory
    {
        public string                   CreateDough()       => "Thin crust dough";
        public string                   CreateSauce()       => "Marinara sauce";
        public string                   CreateCheese()      => "Reggiano cheese";
        public IEnumerable<string>      CreateVeggies()     => new[] { "Garlic", "Onion", "Mushroom", "RedPepper" };
        public string                   CreatePepperoni()   => "Sliced pepperoni";
        public string                   CreateClams()       => "Fresh Clams";
    }
    public class ChicagoIngredientsFactory : IPizzaIngredientFactory
    {
        public string                   CreateDough()       => "Big crust dough";
        public string                   CreateSauce()       => "Red potato sauce";
        public string                   CreateCheese()      => "Shredded mozarella cheese";
        public IEnumerable<string>      CreateVeggies()     => new[] { "Garlic", "Onion", "Mushroom", "RedPepper" };
        public string                   CreatePepperoni()   => "Sliced pepperoni";
        public string                   CreateClams()       => "Fresh Clams";
    }
}
