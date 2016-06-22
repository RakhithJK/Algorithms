using System;
using PizzaStore.Ingredients;
using PizzaStore.Pizzas;

using chicago = PizzaStore.Pizzas.Chicago;
using newYork = PizzaStore.Pizzas.NewYork;

namespace PizzaStore.Stores
{
    public class ChicagoPizzaStore : PizzaStore
    {
        public override Pizza Create(PizzaType type)
        {
            IPizzaIngredientFactory ingredientFactory = new ChicagoIngredientsFactory();
            switch (type)
            {
                case PizzaType.Cheese:
                    return new chicago::CheesePizza(ingredientFactory: ingredientFactory);
                case PizzaType.Pepperoni:
                    return new chicago::PepperoniPizza(ingredientFactory: ingredientFactory);
                case PizzaType.Veggie:
                    return new chicago::VeggiePizza(ingredientFactory: ingredientFactory);
                case PizzaType.Clam:
                    return new chicago::ClamPizza(ingredientFactory: ingredientFactory);
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }   
    }
    public class NewYorkPizzaStore : PizzaStore
    {
        public override Pizza Create(PizzaType type)
        {
            IPizzaIngredientFactory ingredientFactory = new NewYorkIngredientsFactory();
            switch (type)
            {
                case PizzaType.Cheese:
                    return new newYork::CheesePizza(ingredientFactory: ingredientFactory);
                case PizzaType.Pepperoni:
                    return new newYork::PepperoniPizza(ingredientFactory: ingredientFactory);
                case PizzaType.Veggie:
                    return new newYork::VeggiePizza(ingredientFactory: ingredientFactory);
                case PizzaType.Clam:
                    return new newYork::ClamPizza(ingredientFactory: ingredientFactory);
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }
        }
    }
}