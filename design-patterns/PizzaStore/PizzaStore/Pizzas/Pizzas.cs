namespace PizzaStore.Pizzas
{
    public class CheesePizza    : Pizza { }
    public class PepperoniPizza : Pizza { }
    public class VeggiePizza    : Pizza { }
    public class ClamPizza      : Pizza { }

    public enum PizzaType
    {
        Cheese,
        Pepperoni,
        Veggie,
        Clam
    }
}
