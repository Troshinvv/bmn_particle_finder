//
// Created by Misha on 3/15/2023.
//


void lambda(std::string list){
  TFileCollection collection( "collection", "", list.c_str() );
  auto* chain = new TChain( "t" );
  chain->AddFileInfoList( collection.GetList() );
  ROOT::RDataFrame d( *chain );
  


const float PROTON_M = 0.938; // GeV/c2
  const float Y_CM = 1.15141;
  const float FHCAL_Z = 980; // cm

  auto f1_m2_400 = new TF1( "m2_p_400", "pol2", 0, 10 );
  f1_m2_400->SetParameter( 0, 0.965499 );
  f1_m2_400->SetParameter( 1, -0.0625193 );
  f1_m2_400->SetParameter( 2, -0.0217673 );

	auto f1_s_400 = new TF1( "s_p_400", "pol3", 0, 10 );
  f1_s_400->SetParameter( 0, 0.220837 );
  f1_s_400->SetParameter( 1, -0.214113 );
  f1_s_400->SetParameter( 2, 0.161722 );
  f1_s_400->SetParameter( 3, -0.0251886 );
  
  auto f1_m2_700 = new TF1( "m2_p_700", "pol4", 0, 10 );
  f1_m2_700->SetParameter( 0, 1.0847 );
  f1_m2_700->SetParameter( 1, -0.330513 );
  f1_m2_700->SetParameter( 2, 0.220286 );
  f1_m2_700->SetParameter( 3, -0.064973 );
  f1_m2_700->SetParameter( 4, 0.00705849 );

  auto f1_s_700 = new TF1( "s_p_700", "pol3", 0, 10 );
  f1_s_700->SetParameter( 0,  0.102933 );
  f1_s_700->SetParameter( 1,  -0.115384 );
  f1_s_700->SetParameter( 2,  0.088186 );
  f1_s_700->SetParameter( 3,  -0.0115386 );

  auto dd = d
          .Define("primary_vtx", [](double x, double y, double z){
            return std::vector<float>{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
            }, { "vtxX", "vtxY", "vtxZ"})
          .Define("centrality", [](ROOT::VecOps::RVec<float> mom){
            float centrality{-1.f};
            std::vector<float> centrality_percentage{ 0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 90, 100 };
            std::vector<int> multiplicity_edges{ 249, 118, 102, 89, 77, 67, 57, 49, 42, 29, 20, 13, 8, 4, 0 };
            auto multiplicity = mom.size();
            int idx = 0;
            float bin_edge = multiplicity_edges[idx];
            while( multiplicity < bin_edge &&
                   idx < multiplicity_edges.size()-1 ){
              idx++;
              bin_edge = multiplicity_edges[idx];
            }
            centrality = (centrality_percentage[idx-1] + centrality_percentage[idx])/2.0f;
            return centrality;
            }, { "trP" })
          .Define( "pq", " std::vector<float> pq; for( int i=0; i<trMom.size(); i++ ){ pq.push_back( trMom.at(i).P() / trCharge.at(i) ); } return pq;" )
          .Define( "trM2Tof400","std::vector<float> vec_m2;\n"
                    "for( int i=0; i<trMom.size(); i++ ){\n"
                    " auto p = trMom.at(i).P();\n"
                    " auto p2 = p*p;\n"
                    " auto beta = trBetaTof400.at(i);\n"
                    " auto beta2 = beta*beta;\n"
                    " auto gamma2 = 1 - beta2;\n"
                    " auto m2 = beta > -990. ? p2 / beta2 * gamma2 : -999.0;\n"
                    " vec_m2.push_back( m2 );\n"
                    "}\n"
                    "return vec_m2;" )
          .Define( "trM2Tof700","std::vector<float> vec_m2;\n"
                    "for( int i=0; i<trMom.size(); i++ ){\n"
                    " auto p = trMom.at(i).P();\n"
                    " auto p2 = p*p;\n"
                    " auto beta = trBetaTof700.at(i);\n"
                    " auto beta2 = beta*beta;\n"
                    " auto gamma2 = 1 - beta2;\n"
                    " auto m2 = beta > -990. ? p2 / beta2 * gamma2 : -999.0;\n"
                    " vec_m2.push_back( m2 );\n"
                    "}\n"
                    "return vec_m2;" )
                   .Define( "trIsProton400", [ f1_m2_400, f1_s_400 ]( 
                std::vector<float> vec_m2, 
                std::vector<float> vec_pq 
                ){
                  std::vector<int> vec_is{};
                  vec_is.reserve( vec_pq.size() );
                  for( int i=0; i < vec_pq.size(); ++i ){
                    auto pq = vec_pq.at(i);
                    auto m2 = vec_m2.at(i);
                    if( pq < 0 ){ vec_is.push_back(0); continue; }
                    auto mean = f1_m2_400->Eval(pq);
                    auto sigma = f1_s_400->Eval(pq);
                    auto lo = mean - 3*sigma;
                    auto hi = mean + 3*sigma;
                    vec_is.push_back( lo < m2 && m2 < hi ? 1 : 0 );
                  }
                  return vec_is;
                }
                ,{ "trM2Tof400", "pq" } )
          .Define( "trIsProton700", [ f1_m2_700, f1_s_700 ]( 
                std::vector<float> vec_m2, 
                std::vector<float> vec_pq 
                ){
                  std::vector<int> vec_is{};
                  vec_is.reserve( vec_pq.size() );
                  for( int i=0; i < vec_pq.size(); ++i ){
                    auto pq = vec_pq.at(i);
                    auto m2 = vec_m2.at(i);
                    if( pq < 0 ){ vec_is.push_back(0); continue; }
                    auto mean = f1_m2_700->Eval(pq);
                    auto sigma = f1_s_700->Eval(pq);
                    auto lo = mean - 3*sigma;
                    auto hi = mean + 3*sigma;
                    vec_is.push_back( lo < m2 && m2 < hi ? 1 : 0 );
                  }
                  return vec_is;
                }
                ,{ "trM2Tof700", "pq" } )
          .Define( "trIsProton", []( std::vector<int> is_400, std::vector<int> is_700 ){
                  std::vector<int> vec_is{};
                  vec_is.reserve( is_400.size() );
                  for( int i=0; i<is_400.size(); ++i ){ vec_is.push_back( is_400.at(i) == 1 || is_700.at(i) == 1 ? 1 : 0 ); }
                  return vec_is;
                }, {"trIsProton400", "trIsProton700"} )
         /* .Define("pdg_vector", [](ROOT::VecOps::RVec<short> trCharge ){
            std::vector<int> pdg;
            int pr = 0;
            int pi =0;
            for( auto idx : trCharge ) {
              if( idx < 0 ) {
                pdg.push_back(-999);
                continue;
              }
              if( idx >= trCharge.size() ) {
                pdg.push_back(-999);
                continue;
              }
              if(trCharge.at(idx)==-1){
                pdg.push_back(-211);
                pi++;
                continue;
              }
              if(trCharge.at(idx)==1){
                pdg.push_back(2212);
                pr++;
                continue;
              }
            }
            std::cout<<pr<<" "<<pi<<endl;
            return pdg;
            }, { "trCharge" })*/
           .Define("pdg_vector", [](const std::vector<std::vector<float>>& track_parameters, std::vector<int> is_pr ){
            std::vector<int> pdg;
            int pr = 0;
            int pi =0;
            for( int idx=0;idx<track_parameters.size();++idx ) {
              const auto trk_parameters = track_parameters.at(idx);
    const auto qp = trk_parameters.at(5);
    const auto p = fabsf( 1.0f / qp );
    const auto q = qp * p;
              if(q==-1){
                pdg.push_back(-211);
                pi++;
                continue;
              }
              if(q==1 && is_pr.at(idx)==1 ){
                pdg.push_back(2212);
                pr++;
                continue;
              }
              pdg.push_back(-999);
            }
      //      std::cout<<pr<<" "<<pi<<endl;
            return pdg;
            }, { "stsTrackParameters", "trIsProton" })
            .Define("is_good_track", [](std::vector<int> pdg_vector, std::vector<float> chi2_ndf){
            std::vector<int> is_good;
            int pr = 0;
            int pi=0;
            for(int i=0;i<pdg_vector.size();i++){
              auto pid = pdg_vector.at(i);
              auto chi2 = chi2_ndf.at(i);
              if( chi2 < 0.5 ){
                is_good.push_back(0);
                continue;
              }
              if(pid==2212) {
                is_good.push_back(1);
               pr++; 
                continue;}
              if(pid==-211) {
                is_good.push_back(1);
                 pi++;
                continue;}
              is_good.push_back(0);
            }
          //   std::cout<<pr<<" "<<pi<<endl;
            return is_good;
            }, {"pdg_vector", "stsTrackChi2Ndf" })
            ;


  Finder finder;
  finder.AddDecay("lambda",
//                  MotherConfig().SetPdg(3122).SetL(2.25).SetLdL(6.25).SetChi2Geo(40).SetDca(0.728),
                  MotherConfig().SetPdg(3122),
                  {
//    DaughterConfig().SetPdg(-211).SetChi2Prim(535),
    DaughterConfig().SetPdg(-211),
//    DaughterConfig().SetPdg(2212).SetChi2Prim(50).SetCos(0.99),
    DaughterConfig().SetPdg(2212),
    });
//  finder.AddDecay("lambda", 3122, {-211, 2212});
  auto ddd = dd.Filter("10 < centrality && centrality < 40")
          .Define( "candidates", finder, {"primary_vtx",
                                           "stsTrackParameters",
                                           "stsTrackCovMatrix",
                                           "stsTrackMagField",
                                           "pdg_vector",
                                           "is_good_track"} )
          .Define("candidate_momenta", Getters::GetMomenta, {"candidates"} )
          .Define("candidate_mass", Getters::GetMass, {"candidates"} )
          .Define("candidate_momentum_errors", Getters::GetMomentumErr, {"candidates"} )
          .Define("candidate_pid", Getters::GetPDG, {"candidates"} )
          .Define("daughter_cosines", Getters::GetDaughterCosines, {"candidates"} )
          .Define("daughter_chi2_prim", Getters::GetDaughterChi2PV, {"candidates"} )
          .Define("candidate_cos_topo", Getters::GetCosineTopo, {"candidates"} )
          .Define("daughter_dca", Getters::GetDaughterDCA, {"candidates"} )
          .Define("distance_to_sv", Getters::GetDistanceToSV, {"candidates"} )
          .Define("candidate_L", Getters::GetL, {"candidates"} )
          .Define("candidate_LdL", Getters::GetLdL, {"candidates"} )
          .Define("candidate_chi2_geo", Getters::GetChi2Geo, {"candidates"} )
          .Define("candidate_chi2_topo", Getters::GetChi2Topo, {"candidates"} )
          ;
  auto fields = ddd.GetColumnNames();
  std::vector<std::string> exclude_fields{"candidates", "primary_vtx", "primary_vtx", "is_good_track"};
//  std::vector<std::string> exclude_fields{};
  std::vector<std::string> white_list{};
  for(const auto& field : fields){
    if( std::find(exclude_fields.begin(), exclude_fields.end(), field) != exclude_fields.end() )
      continue;
    if( auto dot_pos = field.find("."); dot_pos != std::string::npos )
      continue;
    white_list.push_back( field );
  }
  std::cout << "Fields to be written to the output tree: " << "\n";
  for( auto field : white_list )
    std::cout << field << "\n";
  ddd.Snapshot("t", "candidates.root", white_list );

}
