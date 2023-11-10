void rec_lambda_qa(){
	ROOT::RDataFrame d("t", "candidates.root");
	auto dd = d
//      .Filter("centrality > 10.0")
			.Define( "candidate_pT", "std::vector<float> pT; for( auto mom : candidate_momenta ){ pT.push_back( mom.Pt() ); } return pT;")
			.Define("candidate_phi", "std::vector<float> phi; for( auto mom : candidate_momenta ){ phi.push_back( mom.Phi() ); } return phi;")
			.Define("candidate_rapidity", "std::vector<float> rapidity; for( auto mom : candidate_momenta ){ rapidity.push_back( mom.Rapidity() ); } return rapidity;")
			.Define("pT_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(0) ); } return err;")
			.Define("phi_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(1) ); } return err;")
			.Define("eta_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(2) ); } return err;")
			.Define("m_err", "std::vector<float> err; for( auto mom : candidate_momentum_errors ){ err.push_back( mom.at(3) ); } return err;")
			.Define("daughter1_cos", "std::vector<float> cosine; for( int i=0; i<daughter_cosines.at(0).size(); ++i ){ cosine.push_back( daughter_cosines.at(0).at(i) ); } return cosine;")
			.Define("daughter2_cos", "std::vector<float> cosine; for( int i=0; i<daughter_cosines.at(1).size(); ++i ){ cosine.push_back( daughter_cosines.at(1).at(i) ); } return cosine;")
			.Define("daughter1_chi2_prim", "std::vector<float> chi2; for( int i=0; i<daughter_chi2_prim.at(0).size(); ++i ){ chi2.push_back( daughter_chi2_prim.at(0).at(i) ); } return chi2;")
			.Define("daughter2_chi2_prim", "std::vector<float> chi2; for( int i=0; i<daughter_chi2_prim.at(1).size(); ++i ){ chi2.push_back( daughter_chi2_prim.at(1).at(i) ); } return chi2;")
	//		.Define("candidate_chi2_geo_1", "std::vector<float> chi2; for( int i=0; i<chi2_geo.at(0).size(); ++i ){ chi2.push_back( chi2_geo.at(0).at(i) ); } return chi2;")
	//		.Define("candidate_chi2_topo", "std::vector<float> chi2; for( int i=0; i<chi2_topo.at(0).size(); ++i ){ chi2.push_back( chi2_topo.at(0).at(i) ); } return chi2;")
	//		.Define("candidate_cosine_topo", "std::vector<float> cosine; for( int i=0; i<cos_topo_.at(0).size(); ++i ){ cosine.push_back( cos_topo_.at(0).at(i) ); } return cosine;")
			.Define("good_candidate",
					"std::vector<int> good_candidate;"
					"for(int i=0; i<daughter_chi2_prim.at(0).size(); ++i){"
						"if( m_err.at(i)*2*candidate_mass.at(i) > 0.001 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
					/*	"if( candidate_cos_topo.at(i) < 0.99 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"*/
                                                "if( daughter2_cos.at(i) < 0.99 ){"
                                                        "good_candidate.push_back(0);"
                                                        "continue;"
                                                "}"
						"if( daughter1_chi2_prim.at(i) < 535 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( daughter2_chi2_prim.at(i) < 50 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_L.at(i) < 2.25 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_LdL.at(i) < 6.25 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
						"if( candidate_chi2_topo.at(i) > 51 ){"
							"good_candidate.push_back(0);"
							"continue;"
						"}"
                                                 "if( candidate_chi2_geo.at(i) < 40  ){"
                                                        "good_candidate.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter_dca.at(i) < 0.728  ){"
                                                        "good_candidate.push_back(0);"
                                                        "continue;"
                                                "}"
					
						"good_candidate.push_back( 1 );"
					"} return good_candidate;"
			)
         .Define("basic_cut",
                                        "std::vector<int> basic_cut;"
                                        "for(int i=0; i<daughter_chi2_prim.at(0).size(); ++i){"
                                                "if( m_err.at(i)*2*candidate_mass.at(i) > 0.001 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"
                                               /* "if( candidate_cos_topo.at(i) < 0.99 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"*/
                                                "if( daughter2_cos.at(i) < 0.99 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( candidate_L.at(i) < 2.25 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( candidate_LdL.at(i) < 6.25 ){"
                                                        "basic_cut.push_back(0);"
                                                        "continue;"
                                                "}"

                                                "basic_cut.push_back( 1 );"
                                        "} return basic_cut;"
                        )
          .Define("basic_var",
                                        "std::vector<int> basic_var;"
                                        "for(int i=0; i<daughter_chi2_prim.at(0).size(); ++i){"
                                                "if( m_err.at(i)*2*candidate_mass.at(i) > 0.001 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter2_cos.at(i) < 0.99 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter1_chi2_prim.at(i) < 535 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                               /* "if( daughter2_chi2_prim.at(i) < 50 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"*/
                                                "if( candidate_L.at(i) < 2.25 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( candidate_LdL.at(i) < 6.25 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                /*"if( candidate_chi2_topo.at(i) > 51 ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"*/
                                                 "if( candidate_chi2_geo.at(i) < 40  ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"
                                                "if( daughter_dca.at(i) < 0.728  ){"
                                                        "basic_var.push_back(0);"
                                                        "continue;"
                                                "}"

                                                "basic_var.push_back( 1 );"
                                        "} return basic_var;"
                        )


			
	;

	std::vector<ROOT::RDF::RResultPtr<::TH1D>> hist1d;
	std::vector<ROOT::RDF::RResultPtr<::TH2D>> hist2d;
        std::vector<std::string> cuts {"good_candidate", "basic_cut", "basic_var"};
	hist1d.push_back( dd.Histo1D( { "h1_mass", ";m (GeV/c^2); counts", 100, 1.05, 1.25 }, "candidate_mass" ) );
	hist1d.push_back( dd.Histo1D( { "h1_pT", ";p_{T} (GeV/c); counts", 100, 0.00, 2.0 }, "candidate_pT" ) );
	hist1d.push_back( dd.Histo1D( { "h1_phi", ";#varphi (rad); counts", 100, -3.50, 3.5 }, "candidate_phi" ) );
	hist1d.push_back( dd.Histo1D( { "h1_rapdity", ";y_{lab}; counts", 100, 0.0, 3.5 }, "candidate_rapidity" ) );
	hist1d.push_back( dd.Histo1D( { "h1_pT_err", ";#Deltap_{T}; counts", 100, 0.0, 0.1 }, "pT_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_phi_err", ";#Delta#varphi; counts", 100, 0.0, 0.1 }, "phi_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_eta_err", ";#Delta#eta; counts", 100, 0.0, 0.1 }, "eta_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_mass_err", ";#Deltam; counts", 100, 0.0, 0.05 }, "m_err" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter1_cos", ";cos(#varphi_{1}); counts", 100, 0.8, 1.0 }, "daughter1_cos" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter2_cos", ";cos(#varphi_{2}); counts", 100, 0.98, 1.0 }, "daughter2_cos" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter1_chi2_prim", ";#chi^{2}_{prim}^{1}; counts", 500, 0.0, 1000.0 }, "daughter1_chi2_prim" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter2_chi2_prim", ";#chi^{2}_{prim}^{2}; counts", 150, 0.0, 300.0 }, "daughter2_chi2_prim" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_chi2_geo", ";#chi^{2}_{geo}; counts", 500, 0.0, 100.0 }, "candidate_chi2_geo" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_chi2_topo", ";#chi^{2}_{topo}; counts", 150, 0.0, 150.0 }, "candidate_chi2_topo" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_cos_topo", ";r_{#lambda}p_{#lambda}; counts", 100, 0.98, 1.0 }, "candidate_cos_topo" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter_dca", ";DCA; counts", 200, 0.0, 1 }, "daughter_dca" ) );
	hist1d.push_back( dd.Histo1D( { "h1_daughter_distance_to_sv", ";DCA_{prim}; counts", 100, 0.0, 10.0 }, "distance_to_sv" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_L", ";L; counts", 100, 0.0, 20.0 }, "candidate_L" ) );
	hist1d.push_back( dd.Histo1D( { "h1_candidate_LdL", ";L/dL; counts", 100, 0.0, 20.0 }, "candidate_LdL" ) );
	hist2d.push_back( dd.Histo2D( { "h2_pT_y", ";y;p_{T} (GeV/c)", 30, 0.0, 3.0, 25, 0.0, 2.5  }, "candidate_rapidity", "candidate_pT" ) );
       
 hist2d.push_back( dd.Histo2D( { "h2_m_err_m_inv", ";#Deltam (GeV/c^2);m_inv (GeV/c^2)", 100, 0.0, 0.01, 100, 1.05, 1.25  }, "m_err", "candidate_mass" ) );
 hist2d.push_back( dd.Histo2D( { "h2_pi_chi2_prim_m_inv", ";#chi^{2}_{prim}^{1};m_inv (GeV/c^2)", 100, 0.0, 300, 100, 1.05, 1.25  }, "daughter1_chi2_prim", "candidate_mass" ) );       
 hist2d.push_back( dd.Histo2D( { "h2_chi2_topo_m_inv", ";#chi^{2}_{topo};m_inv (GeV/c^2)", 100, 0.0, 100, 100, 1.05, 1.25  }, "candidate_chi2_topo", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_p_chi2_prim_m_inv", ";#chi^{2}_{prim}^{2};m_inv (GeV/c^2)", 100, 0.0, 100, 100, 1.05, 1.25  }, "daughter2_chi2_prim", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_p_lam_m_inv", ";cos(#varphi_{2});m_inv (GeV/c^2)", 100, 0.98, 1, 100, 1.05, 1.25  }, "daughter2_cos", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_dca_m_inv", ";DCA;m_inv (GeV/c^2)", 200, 0.0, 2, 100, 1.05, 1.25  }, "daughter_dca", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_chi2_geo_m_inv", ";#chi^{2}_{geo};m_inv (GeV/c^2)", 50, 0.0, 100, 100, 1.05, 1.25  }, "candidate_chi2_geo", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_L_m_inv", ";L;m_inv (GeV/c^2)", 80, 0.0, 20, 100, 1.05, 1.25  }, "candidate_L", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_LdL_m_inv", ";L/dL;m_inv (GeV/c^2)", 160, 0.0, 40, 100, 1.05, 1.25  }, "candidate_LdL", "candidate_mass" ) );
hist2d.push_back( dd.Histo2D( { "h2_cos_topo_m_inv", ";r_{#lambda}p_{#lambda};m_inv (GeV/c^2)", 100, 0.98, 1, 100, 1.05, 1.25  }, "candidate_cos_topo", "candidate_mass" ) );
	
	for( auto cut : cuts ){
		hist1d.push_back( dd.Histo1D( { std::data("h1_mass_"+cut), ";m (GeV/c^2); counts", 100, 1.05, 1.25 }, "candidate_mass", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_pT_"+cut), ";p_{T} (GeV/c); counts", 100, 0.00, 2.0 }, "candidate_pT", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_phi_"+cut), ";#varphi (rad); counts", 100, -3.50, 3.5 }, "candidate_phi", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_rapdity_"+cut), ";y_{lab}; counts", 100, 0.0, 3.5 }, "candidate_rapidity", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_pT_err_"+cut), ";#Deltap_{T}; counts", 100, 0.0, 0.1 }, "pT_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_phi_err_"+cut), ";#Delta#varphi; counts", 100, 0.0, 0.1 }, "phi_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_eta_err_"+cut), ";#Delta#eta; counts", 100, 0.0, 0.1 }, "eta_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_mass_err_"+cut), ";#Deltam; counts", 100, 0.0, 0.05 }, "m_err", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter1_cos_"+cut), ";cos(#varphi_{1}); counts", 100, 0.8, 1.0 }, "daughter1_cos", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter2_cos_"+cut), ";cos(#varphi_{2}); counts", 100, 0.98, 1.0 }, "daughter2_cos", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter1_chi2_prim_"+cut), ";#chi^{2}_{prim}^{1}; counts", 500, 0.0, 1000.0 }, "daughter1_chi2_prim", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter2_chi2_prim_"+cut), ";#chi^{2}_{prim}^{2}; counts", 150, 0.0, 300.0 }, "daughter2_chi2_prim", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_chi2_geo_"+cut), ";#chi^{2}_{geo}; counts", 500, 0.0, 100.0 }, "candidate_chi2_geo", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_chi2_topo_"+cut), ";#chi^{2}_{topo}; counts", 150, 0.0, 150.0 }, "candidate_chi2_topo", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_cos_topo_"+cut), ";r_{#lambda}p_{#lambda}; counts", 100, 0.98, 1.0 }, "candidate_cos_topo", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter_dca_"+cut), ";DCA; counts", 100, 0.0, 1 }, "daughter_dca", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_daughter_distance_to_sv_"+cut), ";DCA_{prim}; counts", 100, 0.0, 10.0 }, "distance_to_sv", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_L_"+cut), ";L; counts", 100, 0.0, 20.0 }, "candidate_L", cut ) );
			hist1d.push_back( dd.Histo1D( { std::data("h1_candidate_LdL_"+cut), ";L/dL; counts", 100, 0.0, 20.0 }, "candidate_LdL", cut ) );
			hist2d.push_back( dd.Histo2D( { std::data("h2_pT_y_"+cut), ";y;p_{T} (GeV/c)", 30, 0.0, 3.0, 25, 0.0, 2.5  }, "candidate_rapidity", "candidate_pT", cut ) );
	}
	auto file_out = TFile::Open("rec_lambda_qa.root", "recreate");
	for( auto& h1 : hist1d )
		h1->Write();
	for( auto& h2 : hist2d )
		h2->Write();
	file_out->Close();
}
