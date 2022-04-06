#include "Game.h"
#include "../Control/States/OptionsState.h"


void Game::loadSpriteSheets()
{
    string filename = "../Images/config/resources.json";

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing '" + filename + "'";
    }

    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    // load tilesets
    jValue = root["tilesets"];
    if (jValue != nullptr) {
        if (jValue->IsArray()) {
            for (auto& v : jValue->AsArray()) {
                if (v->IsObject()) {
                    JSONObject vObj = v->AsObject();
                    std::string key = vObj["id"]->AsString();
                    std::string file = vObj["file"]->AsString();
                    auto a = new Texture(renderer, file);
                    tilesets_.emplace(std::make_pair(key, a));
                }
                else {
                    throw "'tilesets' array in '" + filename
                        + "' includes and invalid value";
                }
            }
        }
        else {
            throw "'tilesets' is not an array";
        }
    }
}

void Game::updateCameraPos()
{
    Vector2D<float> v = { (float)player_->getPosition().getX() - getWindowWidth() / 2, (float)player_->getPosition().getY() - getWindowHeight() / 2 };
    mCamera_->setPos(v);
}

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false), mCamera_(nullptr), mapOpened(false), mapPoint(nullptr)
{
    SDLUtils::init("Monkey Delivery", 1800, 1000,
        "../Images/config/resources.json");

    setRenderer(sdlutils().renderer());
   
    font_ = new Font("../Images/TheMoon.ttf", 50);

    string path = "../Images/Mapa/imagenMiniMapa.png";
    maptexture = new Texture(getRenderer(), path);
}

Game::~Game() {

    for (auto gO : gameObjects_)
    {
        delete gO;
    }
    for (auto enemy : enemyContainer_)
        delete enemy;

    for (auto col : collisions_)
        delete col;
    collisions_.clear();
    gameObjects_.clear();
    enemyContainer_.clear();
    cout << "[DEBUG] deleting game" << endl;
    delete player_;
    delete textureContainer_;
    delete font_;
    delete info;
    delete optionsState;
    //delete missionsPanel_; //solo poner si no va en el vector de gameobjects
    delete dialogueBox_;
    delete iE_;
    delete animationManager;
    delete shop_;
    delete mCamera_;
    delete mapPoint;
    for (auto a : tilesets_) {
        a.second->free();
        delete a.second;
    }
    for (auto x : savedStates) {
        delete x;
    }
    SDL_SetWindowBrightness(sdlutils().window(), 1);

    delete maptexture; maptexture = nullptr;
}

void Game::add(GameObject* gameObject) {//a�adir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::removeGameObject(GameObject* gameObject){
    delete gameObject;
    //es necesario el for qui pq si no luego antes de llegar al update peta
    for (int i = 0; i < gameObjects_.size(); i++){
        if (gameObjects_[i] == gameObject) {
            gameObjects_.erase(gameObjects_.begin() + i);
            break;
        }
    }
}

void Game::start()
{
    inGame = true;

    mapInfo.path = ".\\Src\\TilemapSrc\\MainMap.tmx";
    loadMap(mapInfo.path);

    animationManager = new AnimationManager(this);
    player_ = new Player(this, animationManager); //Creacion del jugador

    // Cámara:
    Vector2D<float> vJug = { (float)player_->getPosition().getX() - width / 2, (float)player_->getPosition().getY() - height / 2 };
    mCamera_ = new Camera(this, vJug, CAMSIZE_.getX(), CAMSIZE_.getY()); // Tamaño que se ve del mapa -> debe conservar la proporción de la ventana

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_);
    
    mapPoint = new MAPPoint(this);
    add(new IntectuableShop(this, 300, 40));
    shop_ = new Shop(player_, this);

    add(new InteractuableChest(this, 400, 400, 100, 100));

    add(new TutorialBook(this, 500, 500, 100, 75));

    enemiesCreation();//creacion de enemigos

    dialogueBox_ = new DialogueBox(this);
    // dialogueBox_->changeText("DialogueBox1");
    // dialogueBox_->show();
    info = new UI_Info(this);
    auto* x = new Bed(this);
    x->setPosition(670, 760);
    player_->bedPos(670, 760);
    add(x);
    add(new Rock(this,100,700));
}

void Game::update()
{
    player_->update();
   
    updateCameraPos();

    for (auto c : collisions_) {
        if (c->getPosition().getX() && c->collide(player_->getCollider())) {
            //cout << "player colliding\n";
        }
    }

    for (auto gO : gameObjects_) {

        if (gO != nullptr) 
            gO->update();
       /* else {
            gameObjects_.erase()
        }*/
            
    }

    for (auto enemy : enemyContainer_)
        enemy->update();

}

//Normal draw for entities(no Tiles)
void Game::draw()
{
    // Dibujado del mapa
    SDL_Rect dst = { 0, 0, getWindowWidth(), getWindowHeight() };
    SDL_Rect src = { mCamera_->getCameraPosition().getX() / (getWindowWidth() / mCamera_->getWidth()),
                     mCamera_->getCameraPosition().getY() / (getWindowHeight() / mCamera_->getHeight()),
                     mCamera_->getWidth(),
                     mCamera_->getHeight() };
    SDL_RenderCopy(renderer, background_, &src, &dst);

  
    for (auto gO : gameObjects_)
        if(gO!=nullptr)
        gO->draw();

    
    for (auto enemy : enemyContainer_)
        enemy->draw();
    

    info->draw();

    missionsPanel_->draw();

    dialogueBox_->draw();

    player_->draw();

    if (!mapOpened) drawMap();
}

Point2D<int> Game::getOrigin() {
    return { int(-(player_->getX() - player_->getWidth())), 0 };
}

void Game::useInventory(int slot)
{
    player_->useObject(slot);
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer_ = new TextureContainer(renderer);
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer_->getTexture(name);
}

void Game::renderText(string text, int x, int y, SDL_Color color)
{
    font_->render(renderer, text.c_str(), x, y, color);
}

void Game::renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color)
{
    for (int i = 0; i < text.size(); ++i) {
        font_->render(renderer, text[i].c_str(), x, y, color);
        x += incX;
        y += incY;
    }
}

//economy
//modifica el dinero del jugador y devulve bool de confirmaci�n en caso de compra
//actua como enlace al m�todo del jugador
bool Game::changeMoneyPlayer(int money)
{
    return player_->moneyChange(money);
}

//adri y simona: colisiones
vector<GameObject*> Game::getCollisions(SDL_Rect rect)
{
    vector<GameObject*>interactEnt;

    // for que recorre el vector de gameobjects
    for (int i = 0; i < gameObjects_.size(); i++)
    {
        // gameObjects_[i]->isInteractive() quitar�a esto del if
        if (gameObjects_[i]->collide(rect)) {
            interactEnt.push_back(gameObjects_[i]);
        }
    }

    return interactEnt;
}

// devuelve la iE 
InteractiveEntity* Game::getiE()
{
    return iE_;
}
void Game::addEnemies(Enemy* enemy)
{
    enemyContainer_.push_back(enemy);
}
void Game::enemiesCreation()
{
     //zona derecha desde el inicio (pradera)
    addEnemies(new Plant(this, 60, Point2D<int>(1100, 200), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(1200, 350), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(1600, 450), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(1700, 600), animationManager));

    //zona inferior izquierda desde el inicio(camino junto al mar)
    addEnemies(new Cat(this, 50, Point2D<int>(-100, 1300), animationManager));
    addEnemies(new Cat(this, 50, Point2D<int>(-200, 1100), animationManager));

    //zona inferior izquierda desde el inicio(cruce)
    addEnemies(new Scorpion(this, 80, Point2D<int>(-300, 1650), animationManager));
    addEnemies(new Scorpion(this, 80, Point2D<int>(-500, 1850), animationManager));

    //zona inferior izquierda desde el inicio(ante zona al puente isla del sur)
    addEnemies(new Cat(this, 50, Point2D<int>(-1000, 2300), animationManager));
    addEnemies(new Cat(this, 50, Point2D<int>(-250, 2450), animationManager));
    addEnemies(new Scorpion(this, 80, Point2D<int>(-550, 2500), animationManager));

    //zona inferior desde el inicio(bosque)
    addEnemies(new Bat(this, 20, Point2D<int>(450, 1500), 7, animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(800, 1800), 7, animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(1300, 2100), 7, animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(2250, 2000), 7, animationManager));

    addEnemies(new Bull(this, 70, Point2D<int>(1100, 200), animationManager));
}

void Game::scare(double scariness)
{
    player_->getScared(scariness);
}

void Game::interactDialogue()
{
    dialogueBox_->interact();
}


//TILEMAP
void Game::loadMap(string const& filename)
{
    // Se carga la información del .tmx
    mapInfo.tile_map = new tmx::Map();
    mapInfo.tile_map->load(filename);

    // tamaño del mapa
    auto map_dimensions = mapInfo.tile_map->getTileCount();
    mapInfo.rows = map_dimensions.y;
    mapInfo.cols = map_dimensions.x;

    // tamaño de los tiles
    auto tilesize = mapInfo.tile_map->getTileSize();
    mapInfo.tile_width = tilesize.x;
    mapInfo.tile_height = tilesize.y;

    // convertir a textura
    auto rend = renderer;
    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    //SDL_Texture* background_ = SDL_CreateTexture(rend,
    background_ = SDL_CreateTexture(rend,

        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        bgWidth,
        bgHeight
    );
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(background_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, background_);


    //Establecemos los bordes de la camara con respecto al tamaño del tilemap
        //Camera::mainCamera->setBounds(0, 0, mapInfo.cols * mapInfo.tile_width, mapInfo.rows * mapInfo.tile_height);

    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    // (el mapa utiliza el �ndice [gid] del primer tile cargado del tileset como clave)
    // (para poder cargar los tilesets del archivo .tmx, les ponemos de nombre 
    // el nombre del archivo sin extension en el .json) 
    auto& mapTilesets = mapInfo.tile_map->getTilesets();
    for (auto& tileset : mapTilesets) {
        string name = tileset.getName();
        Texture* texture = sdlutils().tilesets().find(name)->second;
        //Texture* texture = tilesets_.find(name)->second;;
        mapInfo.tilesets.insert(pair<uint, Texture*>(tileset.getFirstGID(), texture));
    }
    // recorremos cada una de las capas (de momento solo las de tiles) del mapa
    auto& map_layers = mapInfo.tile_map->getLayers();
    for (auto& layer : map_layers) {
        // aqui comprobamos que sea la capa de tiles
        if (layer->getType() == tmx::Layer::Type::Tile) {
            // cargamos la capa
            tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());

            // obtenemos sus tiles
            auto& layer_tiles = tile_layer->getTiles();

            // recorremos todos los tiles para obtener su informacion
            for (auto y = 0; y < mapInfo.rows; ++y) {
                for (auto x = 0; x < mapInfo.cols; ++x) {
                    // obtenemos el indice relativo del tile en el mapa de tiles
                    auto tile_index = x + (y * mapInfo.cols);

                    // con dicho indice obtenemos el indice del tile dentro de su tileset
                    auto cur_gid = layer_tiles[tile_index].ID;


                    // si es 0 esta vacio asi que continuamos a la siguiente iteracion
                    if (cur_gid == 0)
                        continue;

                    // guardamos el tileset que utiliza este tile (nos quedamos con el tileset cuyo gid sea
                    // el mas cercano, y a la vez menor, al gid del tile)
                    auto tset_gid = -1, tsx_file = 0;;
                    for (auto& ts : mapInfo.tilesets) {
                        if (ts.first <= cur_gid) {
                            tset_gid = ts.first;
                            tsx_file++;
                        }
                        else
                            break;
                    }

                    // si no hay tileset v�lido, continuamos a la siguiente iteracion
                    if (tset_gid == -1)
                        continue;

                    // normalizamos el �ndice
                    cur_gid -= tset_gid;

                    // calculamos dimensiones del tileset
                    auto ts_width = 0;
                    auto ts_height = 0;
                    SDL_QueryTexture(mapInfo.tilesets[tset_gid]->getTexture(),
                        NULL, NULL, &ts_width, &ts_height);

                    // calculamos el area del tileset que corresponde al dibujo del tile
                    auto region_x = (cur_gid % (ts_width / mapInfo.tile_width)) * mapInfo.tile_width;
                    auto region_y = (cur_gid / (ts_width / mapInfo.tile_width)) * mapInfo.tile_height;

                    // calculamos la posicion del tile
                    auto x_pos = x * mapInfo.tile_width;
                    auto y_pos = y * mapInfo.tile_height;


                    //bool is_wall = false; // Booleano de control
                    //// Acceso a las propiedades de una tile dentro de un tileset (.tsx)
                    //vector<tmx::Property> tile_props = mapInfo.tile_map.getTilesets()[tsx_file - 1].getTiles()[cur_gid].properties;
                    //if (tile_props.size() > 0) {
                    //	// Lo separo aqui por si en algun futuro creamos m�s propiedades, realmente habria que hacer una busqueda
                    //	// de la propiedad y si esta en el vector usarla acorde
                    //	if (tile_props[0].getName() == "wall")
                    //		is_wall = tile_props[0].getBoolValue();
                    //}

                    // metemos el tile
                    auto tileTex = mapInfo.tilesets[tset_gid];

                    SDL_Rect src;
                    src.x = region_x; src.y = region_y;
                    src.w = mapInfo.tile_width;
                    src.h = mapInfo.tile_height;

                    SDL_Rect dest;
                    dest.x = x_pos;
                    dest.y = y_pos;
                    dest.w = src.w;
                    dest.h = src.h;

                    int tileRot = layer_tiles[tile_index].flipFlags;
                    float rotCorrection = 45;
                    SDL_RendererFlip tileFlip = SDL_FLIP_NONE;
                    //switch (tileRot)
                    //{
                    //default:break;
                    //case 2:  rotCorrection = 180; break;
                    //case 4:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 45; break;
                    //case 6:  rotCorrection = 225; break;
                    //case 8:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;
                    //case 10:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;
                    //case 12:  rotCorrection = 45; break;
                    //case 14:  rotCorrection = 225; tileFlip = SDL_FLIP_HORIZONTAL; tileFlip = SDL_FLIP_VERTICAL; break;
                    //    /*case 12:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;
                    //    case 14:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;*/
                    //    //case 14:   rotCorrection = 40; break;
                    //}

                    //Multiplicamos por 45 porque esta multiplicado por factor de 45 (lo que devuelve rot)
                    mapInfo.tilesets[tset_gid]->render(src, dest, tileRot * rotCorrection, nullptr, tileFlip);

                }
            }
        }

        if (layer->getType() == tmx::Layer::Type::Object) {
            tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());

            auto& objs = object_layer->getObjects();

            for (auto obj : objs) {
                auto rect = obj.getAABB();

             //   if (obj.getName() == "collision") 
                    auto a = new ColliderTile(this, Vector2D<double>(rect.left, rect.top), rect.width, rect.height );
                    collisions_.push_back(a);
                
            }
        }
    }

    SDL_SetRenderTarget(renderer, nullptr);
}


void Game::initOptionsState()
{
    optionsState = new OptionsState(this);
}

void Game::drawMap()
{ 
    SDL_Rect rectPanel = { minimapinfo_.xOrigin, minimapinfo_.yOrigin, minimapinfo_.w, minimapinfo_.h };
    maptexture->render(rectPanel);

    if (isMapPointerPut) 
        mapPoint->draw();
}

void Game::scalePoint()
{
    int smallDimension = 12;
    int offset = smallDimension / 2;

    mapPoint->setDimension(smallDimension, smallDimension);

    double x = minimapinfo_.xOrigin + (mapPoint->getX() * (minimapinfo_.w / getWindowWidth()) - offset);
    double y = minimapinfo_.yOrigin + (mapPoint->getY() * (minimapinfo_.h / getWindowHeight()) - offset);
   
    mapPoint->setPosition(x, y);
}