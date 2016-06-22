using System.Collections.Generic;
using PizzaStore.Ingredients;

namespace PizzaStore.Pizzas
{
    public class CheesePizza : Pizza
    {
        public CheesePizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
        public override void Prepare()
        {
            base.Prepare();
            Cheese = ingredientFactory.CreateCheese();
        }
    }

    public class PepperoniPizza : Pizza
    {
        public PepperoniPizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
        public string Pepperoni { get; private set; }
        public override void Prepare()
        {
            base.Prepare();
            Pepperoni = ingredientFactory.CreatePepperoni();
        }
    }

    public class VeggiePizza : Pizza
    {
        public VeggiePizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
        public IEnumerable<string> Veggies { get; private set; }
        public override void Prepare()
        {
            base.Prepare();
            Veggies = ingredientFactory.CreateVeggies();
        }
    }
    public class ClamPizza      : Pizza {
        public ClamPizza(IPizzaIngredientFactory ingredientFactory) : base(ingredientFactory) { }
        public string Clam { get; set; }
        public override void Prepare()
        {
            base.Prepare();
            Clam = ingredientFactory.CreateClams();
        }
    }

    public enum PizzaType
    {
        Cheese,
        Pepperoni,
        Veggie,
        Clam
    }
}
