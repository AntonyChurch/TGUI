---
layout: page
title: Introduction to signals
breadcrumb: signals intro
redirect_from:
  - /tutorials/0.8/signals-optional-parameters/
  - /tutorials/0.8/signals-connectEx/
---
<div>
<h3 id="connecting-to-signals">Connecting to signals</h3>
<p>When something happens, widgets can send out a signal (e.g. a button has a "pressed" signal and a checkbox has "checked" and "unchecked" signals). You can bind a signal handler to such a signal with the connect function. The first parameter is the name of the signal, this is the trigger on which the callback should be send. This name is case-insensitive, so it does not matter if you write "pressed" or "Pressed". The second parameter is the function that you want to be called when the signal is send.</p>
<p class="SmallBottomMargin">Here is an example of letting a function get called when a button has been pressed.</p>
{% highlight c++ %}
void signalHandler()
{
    std::cout << "Button pressed" << std::endl;
}

button->connect("pressed", signalHandler);
{% endhighlight %}

<p class="SmallBottomMargin">You could also use lambda functions of course if your function is very small. This is all the code you need to close the window when your quit button gets pressed:</p>
{% highlight c++ %}
quitButton->connect("pressed", [&](){ window.close(); });
{% endhighlight %}

<p class="SmallBottomMargin">The signal handler can also take two parameters: the widget that emitted the signal and the name of the signal.</p>
{% highlight c++ %}
void signalHandler(tgui::Widget::Ptr widget, const std::string& signalName);
editBox->connect("TextChanged", signalHandler);
{% endhighlight %}
</div>

<div>
<h3 id="optional-parameters">Custom parameters</h3>
<p class="SmallBottomMargin">Custom parameters can also be provided. They have to be provided when calling the connect function and will be passed to the signal handler when the event occurs. Keep in mind that when passing a variable, a copy will be made. If the signal handler needs to have access to the original variable, use std::ref.</p>
{% highlight c++ %}
void signalHandler1(int i);
void signalHandler2(tgui::Gui& gui, tgui::Widget::Ptr widget, const std::string& signalName);
editBox->connect("TextChanged", signalHandler1, 5);
editBox->connect("TextChanged", signalHandler2, std::ref(gui));
{% endhighlight %}

<p class="SmallBottomMargin">When connecting class member functions, you must also keep in mind that the first parameter of such function is a hidden 'this' pointer. You must always provide the value of the 'this' pointer manually.</p>
{% highlight c++ %}
struct Class {
    void signalHandler1();
    void signalHandler2(tgui::Widget::Ptr widget, const std::string& signalName);
    void signalHandler3(tgui::Gui& gui, tgui::Widget::Ptr widget, const std::string& signalName);
};

Class instance;

editBox->connect("TextChanged", &Class::signalHandler1, &instance);
editBox->connect("TextChanged", &Class::signalHandler2, &instance);
editBox->connect("TextChanged", &Class::signalHandler3, &instance, std::ref(gui));
{% endhighlight %}
</div>

<div>
<h3 id="optional-parameters">Optional parameters</h3>
<p class="SmallBottomMargin">The widget can optionally provide information about the event that occurred. Since the connect function as shown above does not know at compile time what the signal type is, it cannot use these optional parameters. You must instead connect to the signal directly. The "pressed" signal from buttons e.g. provides the text of the button as optional parameter, so that the signal handler can distinguish which button was pressed.</p>
{% highlight c++ %}
void buttonClickedCallback1();
button->onPress->connect(buttonClickedCallback1);

void buttonClickedCallback2(const sf::String& buttonText);
button->onPress->connect(buttonClickedCallback2);

void buttonClickedCallback3(tgui::Widget::Ptr widget, const std::string& signalName, const sf::String& buttonText);
button->onPress->connect(buttonClickedCallback3);
{% endhighlight %}
</div>

<div>
<h3 id="disconnecting-signals">Disconnecting signals</h3>
<p class="SmallBottomMargin">The connect function returns a unique id, which can be used to diconnect the signal handler.</p>
{% highlight c++ %}
unsigned int id1 = button1->connect("pressed", signalHandler);
button1->disconnect("pressed", id1);

unsigned int id2 = button2->onPress->connect(signalHandler);
button2->onPress->disconnect(id2);
{% endhighlight %}

<p class="SmallBottomMargin">It is also possible to disconnect all signal handlers that connected to a specific signal at once.</p>
{% highlight c++ %}
button1->disconnectAll("pressed");

button2->onPress->disconnectAll();
{% endhighlight %}
</div>