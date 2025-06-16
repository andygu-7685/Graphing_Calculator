#include "graph.h"

string floatToString(float value) {
    std::stringstream ss;
    ss << value; // Automatically trims unnecessary trailing zeros
    return ss.str();
}

graph::graph(graph_info* _infoIn){
    _info = _infoIn;
    plotter = plot(_infoIn);
    pt = sf::CircleShape(2);
    points = vector<sf::Vector2f>(1);

    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "graph() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
}

void graph::set_info(graph_info* _infoIn){
    _info = _infoIn;
    plotter.set_info(_info);
}

void graph::calc_plot(int index, int mode){
    points = plotter(index, mode);
}

void graph::draw(sf::RenderWindow &window){
    sf::Color Gray(128, 128, 128);
    sf::Text xLabel("0", font);
    sf::Text yLabel("0", font);
    xLabel.setCharacterSize(15);
    yLabel.setCharacterSize(15);

    double tickSpacingX = (_info->domain.y - _info->domain.x) / 20.0;
    //round tick spacing to a pleasing number
    int ctr1 = 0;
    while(tickSpacingX < 1){
        tickSpacingX *= 10.0;
        ctr1++;
    }
    tickSpacingX = round(tickSpacingX) / pow(10.0, ctr1);
    assert(tickSpacingX > 0);

    
    //draw vertical grid
    double tickStartX = floor(_info->domain.x / tickSpacingX) * tickSpacingX;
    for(double k = tickStartX; k < _info->domain.y; k += tickSpacingX){
        sf::Vertex ygrid[] = {
        sf::Vertex(sf::Vector2f(k * _info->scale.x + _info->origin.x, 0), Gray),
        sf::Vertex(sf::Vector2f(k * _info->scale.x + _info->origin.x, SCREEN_HEIGHT), Gray)
        };

        //make sure label is always on screen
        if(_info->origin.y + 3.0 < 0)
            xLabel.setPosition(sf::Vector2f(k * _info->scale.x + _info->origin.x + 3.0, 3.0));
        else if (_info->origin.y + 3.0 > SCREEN_HEIGHT)
            xLabel.setPosition(sf::Vector2f(k * _info->scale.x + _info->origin.x + 3.0, SCREEN_HEIGHT - 18.0));
        else
            xLabel.setPosition(sf::Vector2f(k * _info->scale.x + _info->origin.x + 3.0, _info->origin.y + 3.0));

        //Label at max zoom scale
        if(abs(k) < MIN_RANGE / 10.0)
            xLabel.setString("0");
        else
            xLabel.setString(floatToString(k));
    
        window.draw(ygrid, 2, sf::Lines);
        window.draw(xLabel);
    }



    double tickSpacingY = (_info->range.y - _info->range.x) / 20.0;
    int ctr2 = 0;
    while(tickSpacingY < 1){
        tickSpacingY *= 10.0;
        ctr2++;
    }
    tickSpacingY = round(tickSpacingY) / pow(10.0, ctr2);
    assert(tickSpacingY > 0);


    //draw horizontal grid
    double tickStartY = floor(_info->range.x / tickSpacingY) * tickSpacingY;
    for(double d = tickStartY; d < _info->range.y; d += tickSpacingY){
        sf::Vertex xgrid[] = {
        sf::Vertex(sf::Vector2f(0, -(d * _info->scale.y) + _info->origin.y), Gray),
        sf::Vertex(sf::Vector2f(SCREEN_WIDTH - SIDEB_W, -(d * _info->scale.y) + _info->origin.y), Gray)
        };
    

        if(_info->origin.x + 3.0 < 0)
            yLabel.setPosition(sf::Vector2f(3.0, -(d * _info->scale.y) + _info->origin.y + 3.0));
        else if (_info->origin.x + 3.0 > SCREEN_WIDTH - SIDEB_W)
            yLabel.setPosition(sf::Vector2f(SCREEN_WIDTH - SIDEB_W - 18.0, -(d * _info->scale.y) + _info->origin.y + 3.0));
        else
            yLabel.setPosition(sf::Vector2f(_info->origin.x + 3.0, -(d * _info->scale.y) + _info->origin.y + 3.0));


        if(abs(d) < MIN_RANGE / 10.0)
            yLabel.setString("0");
        else
            yLabel.setString(floatToString(d));

        window.draw(xgrid, 2, sf::Lines);
        window.draw(yLabel);
    }


    
    //x and y axis
    sf::Vertex xaxis[] = {
    sf::Vertex(sf::Vector2f(0, _info->origin.y), sf::Color::White),
    sf::Vertex(sf::Vector2f(SCREEN_WIDTH - SIDEB_W, _info->origin.y), sf::Color::White)
    };

    sf::Vertex yaxis[] = {
    sf::Vertex(sf::Vector2f(_info->origin.x, 0), sf::Color::White),
    sf::Vertex(sf::Vector2f(_info->origin.x, SCREEN_HEIGHT), sf::Color::White)
    };
    window.draw(xaxis, 2, sf::Lines);
    window.draw(yaxis, 2, sf::Lines);





    pt.setFillColor(sf::Color(254, 254, 0));

    for(int i = 0; i < points.size() - 1; i++){
    sf::Vertex line[] = {
    sf::Vertex(points[i], sf::Color::Yellow),
    sf::Vertex(points[i + 1], sf::Color::Yellow)
    };

    double xdiff = points[i + 1].x - points[i].x;
    double ydiff = points[i + 1].y - points[i].y;
    if(pow(pow(xdiff, 2) + pow(ydiff, 2), 1/2.0) < 2000)
        window.draw(line, 2, sf::Lines);
    }
    

    pt.setPosition(_info->origin);
    pt.setFillColor(sf::Color(254, 0, 0));
    window.draw(pt);
}